#ifndef PROJECTLISTMODEL_H
#define PROJECTLISTMODEL_H

#include <QSqlTableModel>

class ProjectListModel : public QSqlTableModel
{
    Q_OBJECT
public:
    ProjectListModel();

    QVariant data(const QModelIndex &index, int role) const;

    QHash<int, QByteArray> roleNames() const;

public slots:
    Q_INVOKABLE bool addProject(const QString &projectName);

    QStringList getProjectList();
};

#endif // PROJECTLISTMODEL_H
