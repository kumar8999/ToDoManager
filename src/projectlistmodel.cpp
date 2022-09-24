#include "projectlistmodel.h"

#include <QDebug>
#include <QSqlRecord>
#include <QSqlError>

ProjectListModel::ProjectListModel()
{
    this->setTable("PROJECT_LIST");
    this->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->select();
}

QVariant ProjectListModel::data(const QModelIndex &index, int role) const
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

QHash<int, QByteArray> ProjectListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::UserRole + 1] = "projectName";
    return roles;
}

bool ProjectListModel::addProject(const QString &projectName)
{
    QSqlRecord record = this->record();
    record.setValue(1, projectName);
    this->insertRecord(-1, record);

    bool isOk = this->submitAll();

    return isOk;
}

QStringList ProjectListModel::getProjectList()
{
    QStringList projectList;
    for (int i = 0; i < this->rowCount(); i++) {
        QString projectName = this->record(i).value("PROJECT_NAME").toString();
        projectList.append(projectName);
    }

    return projectList;
}
