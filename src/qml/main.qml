import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15 as Controls
import org.kde.kirigami 2.19 as Kirigami
import org.TodoManager.model 1.0

Kirigami.ApplicationWindow {
    property bool showCompleted: false

    id: root
    title: qsTr("TaskManager")
    width: 700
    height: 600

    pageStack.initialPage: MainWindow {
        title: qsTr("All Tasks")
    }

    ProjectListModel {
        id: projectListModel
    }

    SectionListModel {
        id: sectionListModel
    }
}
