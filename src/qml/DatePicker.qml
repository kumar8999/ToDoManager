import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.15 as Controls
import org.kde.kirigami 2.19 as Kirigami
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.3

Kirigami.Dialog {
    id: dialog

    property var selectedDate: datePicker.selectedDate
    property bool isDateSelected: false

    title: qsTr("Date Picker")

    padding: 0
    preferredWidth: Kirigami.Units.gridUnit * 16

    Calendar {
        id: datePicker

        onClicked: {
            dialog.selectedDate = date
            isDateSelected = true
        }
    }

    footer: Controls.DialogButtonBox {

        Controls.Button {
            text: qsTr("Ok")
            visible: isDateSelected
            Controls.DialogButtonBox.buttonRole: Controls.DialogButtonBox.AcceptRole
        }

        Controls.Button {
            text: qsTr("Clear")
            visible: isDateSelected
            onClicked: {
                isDateSelected = false
            }
        }
    }
}
