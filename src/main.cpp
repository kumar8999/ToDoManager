#include "dbmanager.h"
#include "projectlistmodel.h"
#include "sectionlistmodel.h"
#include "tasklistmodel.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QUrl>
#include <QtQml>

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    auto *dbManager = new DBManager();

    qmlRegisterType<ProjectListModel>("org.TodoManager.model", 1, 0, "ProjectListModel");
    qmlRegisterType<SectionListModel>("org.TodoManager.model", 1, 0, "SectionListModel");
    qmlRegisterType<TaskListModel>("org.TodoManager.model", 1, 0, "TaskListModel");

    engine.rootContext()->setContextProperty("dbManager", dbManager);

    engine.rootContext()->setContextObject(&engine);
    engine.load(QUrl(QStringLiteral("qrc:///qml/main.qml")));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
