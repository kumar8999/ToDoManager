#ifndef SECTIONLISTMODEL_H
#define SECTIONLISTMODEL_H

#include <QSqlTableModel>

class SectionListModel : public QSqlTableModel
{
    Q_OBJECT

    Q_PROPERTY(QString filterProject READ filterProject WRITE setFilterProject NOTIFY
                       filterProjectChanged)

public:
    explicit SectionListModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role) const;

    QHash<int, QByteArray> roleNames() const;

    const QString &filterProject() const;

    void setFilterProject(const QString &newFilterProject);

public slots:
    bool addSection(const QString &projectName, const QString &sectionName);

    QStringList getSectionList(const QString &projectName);

signals:
    void filterProjectChanged();

private:
    QString m_filterProject;
};

#endif // SECTIONLISTMODEL_H
