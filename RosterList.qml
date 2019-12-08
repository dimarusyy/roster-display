import QtQuick 2.0
import App 1.0

ListView {
    id: listView

    property var listModel
    model: listModel

    visible: true
    spacing : 10

    clip: true
    focus: true

    delegate: RosterItem {
        id: rosterItem
        firstName: model.firstName
        lastName: model.lastName

        MouseArea {
            anchors.fill: parent
            onClicked: {
                listView.currentIndex = index;

                rosterDetailsDialog.userName = model.userName
                rosterDetailsDialog.firstName = model.firstName
                rosterDetailsDialog.lastName = model.lastName
                rosterDetailsDialog.sex = model.sex
                rosterDetailsDialog.birthday = model.birthday
                rosterDetailsDialog.country = model.country
                rosterDetailsDialog.language = model.language

                rosterDetailsDialog.visible = true
                console.log("Index [" + index + "], group=[" + model.group + "], groupOrder=[" + model.groupOrder + "]");
            }
        }

        RosterDetailsDialog {
            id: rosterDetailsDialog
            visible: false
            anchors.centerIn: parent
        }
    }
}
