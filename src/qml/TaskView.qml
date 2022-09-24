import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15 as Controls
import org.kde.kirigami 2.19 as Kirigami
import org.TodoManager.model 1.0

Column {
    id: taskListView

    property string projectName: ""
    property bool isPageEmpty: true

    onProjectNameChanged: {
        reloadTask()
    }

    function reloadTask() {
        mainTaskListModel.projectName = projectName
        mainTaskListModel.sectionName = ""
        sectionListModel.filterProject = projectName
    }

    function showInlineMessage(msg, type) {
        inlineMessage.text = msg
        inlineMessage.type = type
        inlineMessage.visible = true
    }

    TaskListModel {
        id: taskListModel
    }

    Kirigami.InlineMessage {
        id: inlineMessage
        width: parent.width
    }

    ListView {
        id: projectTaskList

        height: childrenRect.height
        width: parent.width
        model: mainTaskListModel

        TaskListModel {
            id: mainTaskListModel
        }

        delegate: Kirigami.BasicListItem {
            text: model.taskName
            subtitle: model.description
            leading: Controls.CheckBox {}
        }
    }

    ListView {
        id: sectionListView

        height: childrenRect.height
        width: parent.width
        model: sectionListModel

        delegate: Column {
            width: parent.width

            TaskListModel {
                id: sectionTaskListModel
                sectionName: model.sectionName
                projectName: projectName
            }

            Kirigami.BasicListItem {
                id: taskRow

                property bool expanded: true

                text: model.sectionName
                leading: Kirigami.Icon {
                    source: taskRow.expanded ? "arrow-down" : "arrow-right"
                }

                onClicked: {
                    taskRow.expanded = !taskRow.expanded
                }
            }

            ListView {
                id: sectionChildTaskList

                height: childrenRect.height * opacity
                width: parent.width - x
                visible: opacity > 0
                opacity: taskRow.expanded ? 1 : 0
                model: sectionTaskListModel

                delegate: Kirigami.BasicListItem {
                    text: model.taskName
                    subtitle: model.description
                    leading: Controls.CheckBox {}
                }
            }

            Component.onCompleted: {
                sectionTaskListModel.sectionName = model.sectionName
                sectionTaskListModel.projectName = projectName
            }
        }
    }
}
