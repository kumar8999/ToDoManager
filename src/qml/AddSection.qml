import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.15 as Controls
import org.kde.kirigami 2.19 as Kirigami

Kirigami.Dialog {
    id: addSection

    property string projectName: ''
    property string selectedProjectName: projectName
    signal sectionAdded
    signal sectionAddedFailed

    title: qsTr("Add Section")

    onOpenedChanged: {
        var tempList = ["Inbox"]
        tempList = tempList.concat(projectListModel.getProjectList())
        projectNameField.projectList = tempList
    }

    Kirigami.FormLayout {

        Controls.ComboBox {
            id: projectNameField

            property var projectList: ["Inbox"]

            Kirigami.FormData.label: qsTr("Project Name")
            model: projectList
            currentIndex: projectList.indexOf(projectName)

            delegate: Kirigami.BasicListItem {
                text: modelData
                z: 1001
            }

            onCurrentIndexChanged: {
                selectedProjectName = projectList[currentIndex]
            }
        }

        Controls.TextField {
            id: sectionNameField
            placeholderText: qsTr("Section Name")
            Kirigami.FormData.label: qsTr("Section Name")
        }
    }

    standardButtons: Kirigami.Dialog.Ok | Kirigami.Dialog.Cancel

    onRejected: {
        close()
    }

    onAccepted: {
        if (sectionNameField.text.trim() !== '') {
            var tempProjectName_ = selectedProjectName
            if (tempProjectName_ === "Inbox") {
                tempProjectName_ = ""
            }

            var ok = sectionListModel.addSection(tempProjectName_,
                                                 sectionNameField.text.trim())
            close()

            if (ok) {
                addSection.sectionAdded()
            } else {
                addSection.sectionAddedFailed()
            }
        }
    }
}
