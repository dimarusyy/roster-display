import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.6

import App 1.0

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Display Roster")

    BusyIndicator {
        id: loadingDataIndicator
        anchors.centerIn: parent
    }

    FilteredRosterModel {
        id: rosterModel
        onLoaded: loadingDataIndicator.running = false
        onLoading: loadingDataIndicator.running = true
    }

    ListModel {
        id: rosterRolesModel
        ListElement { text: qsTr("GroupOrder"); value: RosterListModel.GroupOrder }
        ListElement { text: qsTr("UserName"); value: RosterListModel.UserName }
        ListElement { text: qsTr("FirstName"); value: RosterListModel.FirstName }
        ListElement { text: qsTr("LastName"); value: RosterListModel.LastName }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: false
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

            Text {
                id: element
                text: qsTr("Filter")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true
                Layout.fillHeight: true
                font.pixelSize: 12
            }

            TextField {
                id: textField
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredHeight: 20
                Layout.preferredWidth: 256
                placeholderText: qsTr("Text Field")

                onTextChanged: {
                    rosterModel.setFilterFixedString(text)
                }
            }

            ComboBox {
                id: comboBox
                Layout.fillWidth: true
                model: rosterRolesModel
                Layout.fillHeight: true

                onCurrentIndexChanged: {
                    rosterModel.setSortingColumn(model.get(currentIndex).value)
                }
            }
        }

        RosterList {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

            listModel: rosterModel
        }
    }
}

