import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.15 as Controls
import org.kde.kirigami 2.19 as Kirigami

Kirigami.OverlaySheet {
    id: addProject

    signal projectAddFailed
    signal projectAddSucceed

    title: qsTr("Add Project")

    Kirigami.FormLayout {

        Kirigami.InlineMessage {
            id: projectInlineMsg
            width: parent.width
        }

        Controls.TextField {
            id: projectNameField
            placeholderText: qsTr("Project Name")
            Kirigami.FormData.label: qsTr("Project Name")
        }
    }

    footer: Controls.DialogButtonBox {
        standardButtons: Controls.DialogButtonBox.Ok | Controls.DialogButtonBox.Cancel
        onRejected: {
            applicationWindow().pageStack.pop()
        }

        onAccepted: {
            if (projectNameField.text.trim() !== '') {

                var projectList = projectListModel.getProjectList()

                if (projectList.includes(projectNameField.text.trim())) {
                    projectInlineMsg.text = "Duplicate Project Name"
                    projectInlineMsg.visible = true
                    projectInlineMsg.type = Kirigami.MessageType.Error
                    return
                }

                var isOk = projectListModel.addProject(
                            projectNameField.text.trim())

                if (isOk) {
                    projectAddSucceed()
                } else {
                    projectAddFailed()
                }

                addProject.close()
            }
        }
    }
}
