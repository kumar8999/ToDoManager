#include "dbmanager.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QJsonArray>

DBManager::DBManager(QObject *parent) : QObject{ parent }
{
    m_dbPath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);

    if (!m_dbPath.isEmpty()) {
        QDir dir(m_dbPath);
        if (!dir.exists()) {
            dir.mkpath(m_dbPath);
        }

        m_dbPath += "/TaskList.db";

        openConnection();
    }
}

DBManager::~DBManager()
{
    closeConnection();
}

bool DBManager::createTables()
{
    bool success = false;
    QSqlQuery query;

    query.prepare("CREATE TABLE IF NOT EXISTS PROJECT_LIST (ID INTEGER PRIMARY KEY"
                  " AUTOINCREMENT UNIQUE NOT NULL, PROJECT_NAME TEXT UNIQUE NOT NULL)");

    query.exec();

    query.exec("CREATE TABLE IF NOT EXISTS SECTION_LIST (ID INTEGER PRIMARY KEY AUTOINCREMENT "
               "UNIQUE NOT NULL,"
               "PROJECT_NAME TEXT NOT NULL, SECTION_NAME TEXT UNIQUE NOT NULL)");

    query.exec("CREATE TABLE IF NOT EXISTS TASK_LIST (ID INTEGER PRIMARY "
               "KEY AUTOINCREMENT "
               "UNIQUE NOT NULL, TASKNAME TEXT NOT NULL, DESCRIPTION TEXT "
               "NOT NULL DEFAULT '', "
               "PROJECT_NAME TEXT NOT NULL DEFAULT '', SECTION_NAME TEXT "
               "NOT NULL DEFAULT '',"
               "DUE INTEGER, PRIORITY "
               "INTEGER DEFAULT 1, IS_COMPLETED BIT DEFAULT '0');");

    return success;
}

void DBManager::loadDefaults()
{
    QSqlQuery query;
    query.prepare("INSERT INTO PROJECT_LIST (PROJECT_NAME) VALUES ('')");
    query.exec();
}

void DBManager::openConnection()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(m_dbPath);
    if (!m_db.open()) {
        qDebug() << "Error: connection with database failed";
    } else {
        qDebug() << "Database: connection ok";
        createTables();
    }
}

void DBManager::closeConnection()
{
    m_db.close();
}

QJsonArray DBManager::getTaskList(const QString &projectName, const QString &sectionName)
{
    QJsonArray taskList;
    QSqlQuery query;

    query.prepare("SELECT * FROM TASK_LIST WHERE (PROJECT_NAME = :projectName AND SECTION_NAME = "
                  ":sectionName)");
    query.bindValue(":projectName", projectName.trimmed() == "" ? "" : projectName);
    query.bindValue(":sectionName", sectionName.trimmed() == "" ? "" : sectionName);
    query.exec();

    while (query.next()) {

        QString taskName = query.value("TASKNAME").toString();
        QString taskDesc = query.value("DESCRIPTION").toString();
        QString dueDate = query.value("DUE").toString();
        QString priority = query.value("PRIORITY").toString();
        QString isCompleted = query.value("IS_COMPLETED").toString();

        QJsonObject obj;
        obj.insert("taskName", taskName);
        obj.insert("taskDesc", taskDesc);
        obj.insert("dueDate", dueDate);
        obj.insert("priority", priority);
        obj.insert("isCompleted", isCompleted);
        taskList.append(obj);
    }

    return taskList;
}

QJsonArray DBManager::getTaskList(const QString &projectName)
{
    //    QStringList sectionNames = getSectionList(projectName);
    QJsonArray taskList;

    //    for (const auto &sectionName : qAsConst(sectionNames)) {
    //        QJsonObject obj;
    //        obj.insert("sectionName", sectionName);
    //        QJsonArray sectionTasks = getTaskList(projectName, sectionName);
    //        obj.insert("tasks", sectionTasks);
    //        taskList.append(obj);
    //    }

    return taskList;
}

bool DBManager::appendTask(const QString &taskName, const QString &taskDesc,
                           const QString &projectName, const QString &sectionName,
                           const QString &due, const QString &priority, const QString isCompleted)
{
    QSqlQuery query;

    query.prepare("INSERT INTO TASK_LIST (TASKNAME, DESCRIPTION, PROJECT_NAME, SECTION_NAME, DUE, "
                  "PRIORITY, IS_COMPLETED) VALUES (:taskName, :taskDesc, :projectName, "
                  ":sectionName, :due, :priority, :isCompleted);");

    query.bindValue(":projectName", projectName);
    query.bindValue(":taskName", taskName);
    query.bindValue(":taskDesc", taskDesc);
    query.bindValue(":sectionName", sectionName);
    query.bindValue(":due", due);
    query.bindValue(":priority", priority);
    query.bindValue(":isCompleted", isCompleted);
    bool issuccess = query.exec();

    return issuccess;
}
