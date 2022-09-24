#include "tasklistmodel.h"

#include <QSqlRecord>
#include <QDebug>
#include <QSqlError>

TaskListModel::TaskListModel(QObject *parent)
    : m_projectName(""), m_sectionName(""), QSqlTableModel{ parent }
{
    this->setTable("TASK_LIST");
    this->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->select();
    this->setFilter("PROJECT_NAME='' AND SECTION_NAME=''");
}

QVariant TaskListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() >= rowCount()) {
        return QString("");
    }
    if (role < Qt::UserRole) {
        return QSqlQueryModel::data(index, role);
    } else {
        return QSqlQueryModel::data(this->index(index.row(), role - Qt::UserRole), Qt::DisplayRole);
    }
}

QHash<int, QByteArray> TaskListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::UserRole + 1] = "taskName";
    roles[Qt::UserRole + 2] = "description";
    roles[Qt::UserRole + 3] = "projectName";
    roles[Qt::UserRole + 4] = "sectionName";
    roles[Qt::UserRole + 5] = "due";
    roles[Qt::UserRole + 6] = "priority";
    roles[Qt::UserRole + 7] = "isCompleted";
    return roles;
}

const QString &TaskListModel::projectName() const
{
    return m_projectName;
}

void TaskListModel::setProjectName(const QString &newProjectName)
{
    if (m_projectName == newProjectName)
        return;
    m_projectName = newProjectName;
    emit projectNameChanged();

    this->setFilter("PROJECT_NAME='" + newProjectName + "' AND SECTION_NAME='" + m_sectionName
                    + "'");
}

const QString &TaskListModel::sectionName() const
{
    return m_sectionName;
}

void TaskListModel::setSectionName(const QString &newSectionName)
{
    if (m_sectionName == newSectionName)
        return;
    m_sectionName = newSectionName;
    emit sectionNameChanged();

    this->setFilter("PROJECT_NAME='" + m_projectName + "' AND SECTION_NAME='" + m_sectionName
                    + "'");
}

bool TaskListModel::addTasks(const QString &taskName, const QString &taskDesc,
                             const QString &projectName, const QString &sectionName,
                             const QString &due, const QString &priority, const QString isCompleted)
{
    QSqlRecord record = this->record();
    record.setValue(1, taskName);
    record.setValue(2, taskDesc);
    record.setValue(3, projectName);
    record.setValue(4, sectionName.trimmed() == "" ? "" : sectionName.trimmed());
    record.setValue(5, due);
    record.setValue(6, priority);
    record.setValue(7, isCompleted);

    this->insertRecord(-1, record);

    bool isOk = this->submitAll();

    if (isOk) {

        this->setFilter("PROJECT_NAME='" + m_projectName + "' AND SECTION_NAME='" + m_sectionName
                        + "'");
    }

    return isOk;
}
