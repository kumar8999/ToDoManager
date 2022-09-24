#include "sectionlistmodel.h"

#include <QDebug>
#include <QSqlRecord>

SectionListModel::SectionListModel(QObject *parent) : QSqlTableModel{ parent }
{
    this->setTable("SECTION_LIST");
    this->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->select();

    this->setFilter("PROJECT_NAME='" + m_filterProject + "'");
}

QVariant SectionListModel::data(const QModelIndex &index, int role) const
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

QHash<int, QByteArray> SectionListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::UserRole + 1] = "projectName";
    roles[Qt::UserRole + 2] = "sectionName";
    return roles;
}

const QString &SectionListModel::filterProject() const
{
    return m_filterProject;
}

void SectionListModel::setFilterProject(const QString &newFilterProject)
{
    if (m_filterProject == newFilterProject)
        return;
    m_filterProject = newFilterProject;

    emit filterProjectChanged();

    this->setFilter("PROJECT_NAME='" + m_filterProject + "'");
}

bool SectionListModel::addSection(const QString &projectName, const QString &sectionName)
{
    QSqlRecord record = this->record();
    record.setValue(1, projectName);
    record.setValue(2, sectionName);
    this->insertRecord(-1, record);

    bool isOk = this->submitAll();

    return isOk;
}

QStringList SectionListModel::getSectionList(const QString &projectName)
{
    QStringList sectionList;
    for (int i = 0; i < this->rowCount(); i++) {
        QString sectionName = this->record(i).value("SECTION_NAME").toString();
        sectionList.append(sectionName);
    }

    return sectionList;
}
