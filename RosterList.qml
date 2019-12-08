import QtQuick 2.0
import App 1.0

ListView {
    id: listView
    property var listModel

    visible: true
    spacing : 10
    model: listModel
    clip: true

    delegate: RosterItem {
        firstName: model.firstName
        lastName: model.lastName
    }
}
