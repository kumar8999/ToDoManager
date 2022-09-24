import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.15 as Controls
import org.kde.kirigami 2.13 as Kirigami

Kirigami.Page {
    property string projectName: 'Inbox'

    padding: 0

    actions.main: Kirigami.Action {
        icon.name: "overflow-menu"

        Kirigami.Action {
            id: addAction
            icon.name: "list-add"
            text: qsTr("Add Task")
            onTriggered: {
                applicationWindow().pageStack.push("qrc:/qml/AddTaskSheet.qml",
                                                   {
                                                       "projectName": projectName
                                                   })
            }
        }

        Kirigami.Action {
            id: addProjectAction
            icon.name: "list-add"
            text: qsTr("Add Project")
            onTriggered: {
                addProject.open()
            }
        }

        Kirigami.Action {
            text: qsTr("Add Sections")
            icon.name: "list-add"
            onTriggered: {
                addSection.projectName = projectName
                addSection.open()
            }
        }

        Kirigami.Action {
            text: showCompleted ? qsTr("Hide Completed") : qsTr(
                                      "Show Completed")
            icon.name: "check-filled"
            onTriggered: {
                showCompleted = !showCompleted
            }
        }
    }

    Controls.SplitView {
        anchors.fill: parent
        orientation: Qt.Horizontal

        Sidebar {
            id: projectListView
            Controls.SplitView.minimumWidth: 200

            onProjectChanged: {
                projectName = currentProjectName
            }
        }

        TaskView {
            id: taskList
            Controls.SplitView.minimumWidth: 400
            height: parent.height
        }
    }

    onProjectNameChanged: {
        taskList.projectName = projectName
    }

    AddProject {
        id: addProject

        onProjectAddFailed: {
            taskList.showInlineMessage("Error: Cannot Add Project",
                                       Kirigami.MessageType.Error)
        }

        onProjectAddSucceed: {
            taskList.showInlineMessage("Project Added SuccessFully",
                                       Kirigami.MessageType.Positive)
        }
    }

    AddSection {
        id: addSection

        onSectionAdded: {
            taskList.showInlineMessage("Section Added SuccessFully",
                                       Kirigami.MessageType.Positive)
            taskList.reloadTask()
        }

        onSectionAddedFailed: {
            taskList.showInlineMessage("Error: Cannot Add Section",
                                       Kirigami.MessageType.Error)
        }
    }
}
