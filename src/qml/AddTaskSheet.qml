import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.15 as Controls
import org.kde.kirigami 2.19 as Kirigami
import org.TodoManager.model 1.0

Kirigami.ScrollablePage {
    id: addTaskSheet

    property string projectName: ''
    property string selectedProjectName: projectName
    property string sectionName: ''
    property var sectionList: []
    property var projectList: []
    signal taskAdded
    signal taskAddedFailed

    onSelectedProjectNameChanged: {
        var tempProjectName_ = selectedProjectName
        if (tempProjectName_.trim() === "Inbox") {
            tempProjectName_ = ""
        }

        sectionList = sectionListModel.getSectionList(tempProjectName_)
    }

    onTaskAdded: {
        addTaskSheet.showInlineMessage("Added Task",
                                       Kirigami.MessageType.Positive)
    }

    onTaskAddedFailed: {
        addTaskSheet.showInlineMessage("Added Task Failed",
                                       Kirigami.MessageType.Error)
    }

    function showInlineMessage(msg, type) {
        inlineMessage.text = msg
        inlineMessage.type = type
        inlineMessage.visible = true
    }
    header: Kirigami.InlineMessage {
        id: inlineMessage
        width: parent.width
    }

    Kirigami.FormLayout {
        anchors.fill: parent

        Controls.TextField {
            id: taskNameField

            Layout.fillWidth: true
            Kirigami.FormData.label: qsTr("Task Name:")
            placeholderText: qsTr("Task name (required)")
        }

        Controls.TextArea {
            id: descriptionField

            Layout.fillWidth: true
            Kirigami.FormData.label: qsTr("Task Description:")
            placeholderText: qsTr("Task Description")
        }

        Controls.Button {
            id: dateField

            property string label: "Pick Date"
            property var selectedDate

            Layout.fillWidth: true
            Kirigami.FormData.label: qsTr("Due:")
            text: label
            onClicked: {
                datePicker.open()
            }
        }

        Controls.ComboBox {
            id: priorityField

            Layout.fillWidth: true
            Kirigami.FormData.label: qsTr("Priority:")
            model: ["Low", "Medium", "High"]
        }

        Controls.ComboBox {
            id: projectNameField

            Kirigami.FormData.label: qsTr("Project Name")
            model: projectList
            currentIndex: projectList.indexOf(projectName)
            enabled: projectList.length > 1

            delegate: Kirigami.BasicListItem {
                text: modelData
            }

            onCurrentIndexChanged: {
                selectedProjectName = projectList[currentIndex]
            }

            Component.onCompleted: {
                var projectList_ = ["Inbox"]
                projectList_ = projectList_.concat(
                            projectListModel.getProjectList())
                projectList = projectList_
            }
        }

        Controls.ComboBox {
            id: sectionNameNameField

            Kirigami.FormData.label: qsTr("Section Name")
            model: sectionList
            enabled: sectionList.length > 0

            onCurrentIndexChanged: {
                sectionName = sectionList[currentIndex]
            }

            Component.onCompleted: {
                sectionList = sectionListModel.getSectionList(projectName)
            }
        }

        Controls.Button {
            id: doneButton

            Layout.fillWidth: true
            text: qsTr("Done")
            enabled: taskNameField.text.length > 0
            onClicked: {
                var dateTime = 0

                var selectedDate = Date.parse(dateField.selectedDate)
                var tempProjectName_ = projectName
                if (tempProjectName_.trim() === "Inbox") {
                    tempProjectName_ = ""
                }

                var ok = taskListModel.addTasks(taskNameField.text,
                                                descriptionField.text,
                                                tempProjectName_, sectionName,
                                                selectedDate,
                                                priorityField.currentIndex,
                                                false)

                if (ok) {
                    addTaskSheet.taskAdded()
                    timer.start()
                } else {
                    addTaskSheet.taskAddedFailed()
                }
            }
        }
    }

    DatePicker {
        id: datePicker

        onAccepted: {

            if (datePicker.isDateSelected) {
                var date = datePicker.selectedDate
                dateField.text = datePicker.selectedDate.toLocaleDateString(
                            "en_Us")
                dateField.selectedDate = datePicker.selectedDate
            } else {
                dateField.text = "Pick Date"
                dateField.selectedDate = null
            }
        }
    }

    Timer {
        id: timer
        interval: 500

        onTriggered: {
            applicationWindow().pageStack.pop()
        }
    }

    TaskListModel {
        id: taskListModel
    }
}
