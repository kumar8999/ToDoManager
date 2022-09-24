#ifndef DBMANAGAER_H
#define DBMANAGAER_H

#include <QJsonObject>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QVariantList>
#include <QJsonArray>

class DBManager : public QObject
{
    Q_OBJECT

public:
    explicit DBManager(QObject *parent = nullptr);

    ~DBManager();

public slots:

    QJsonArray getTaskList(const QString &projectName, const QString &sectionName);

    QJsonArray getTaskList(const QString &projectName);

    bool appendTask(const QString &taskName, const QString &taskDesc, const QString &projectName,
                    const QString &sectionName, const QString &due, const QString &priority,
                    const QString isCompleted);

signals:
    void projectListChanged();

private:
    void openConnection();

    void closeConnection();

    bool createTables();

    void loadDefaults();

private:
    QSqlDatabase m_db;
    QString m_dbPath;
    bool m_isDBSync;
};

#endif // DBMANAGAER_H
