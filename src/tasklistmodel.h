#ifndef TASKLISTMODEL_H
#define TASKLISTMODEL_H

#include <QSqlTableModel>

class TaskListModel : public QSqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(QString projectName READ projectName WRITE setProjectName NOTIFY projectNameChanged)
    Q_PROPERTY(QString sectionName READ sectionName WRITE setSectionName NOTIFY sectionNameChanged)

public:
    explicit TaskListModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role) const;

    QHash<int, QByteArray> roleNames() const;

    const QString &projectName() const;
    void setProjectName(const QString &newProjectName);

    const QString &sectionName() const;
    void setSectionName(const QString &newSectionName);

signals:
    void projectNameChanged();

    void sectionNameChanged();

public slots:
    bool addTasks(const QString &taskName, const QString &taskDesc, const QString &projectName,
                  const QString &sectionName, const QString &due, const QString &priority,
                  const QString isCompleted);

private:
    QString m_projectName;
    QString m_sectionName;
};

#endif // TASKLISTMODEL_H
