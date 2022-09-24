import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15 as Controls
import org.kde.kirigami 2.19 as Kirigami

ColumnLayout {
    id: sideBar

    property int projectCurIndex: -1
    property string currentProjectName: ''
    property bool isInboxSelected: true
    signal projectChanged(string currentProjectName)

    Kirigami.BasicListItem {
        text: "Inbox"
        highlighted: isInboxSelected

        onClicked: {
            isInboxSelected = true
            projectChanged("")
        }
    }

    ListView {
        id: projectListView

        header: Kirigami.BasicListItem {
            text: qsTr("Projects")

            trailing: Kirigami.Icon {
                source: "add"

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        addProject.open()
                    }
                }
            }
        }

        Layout.fillHeight: true
        Layout.fillWidth: true
        model: projectListModel
        currentIndex: projectCurIndex

        delegate: Kirigami.BasicListItem {
            text: model.projectName

            highlighted: !isInboxSelected
                         && index === projectListView.currentIndex

            onClicked: {
                isInboxSelected = false
                projectChanged(modelData)
            }
        }
    }
}
