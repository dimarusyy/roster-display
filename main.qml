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

    RosterListModel {
        id: rosterListModel
        onLoaded: loadingDataIndicator.running = false
        onLoading: loadingDataIndicator.running = true
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
                font.pixelSize: 12
            }

            TextField {
                id: textField
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredHeight: 20
                Layout.preferredWidth: 256
                placeholderText: qsTr("Text Field")
            }

            Button {
                id: button
                text: qsTr("Apply")
                Layout.preferredHeight: 23
                Layout.preferredWidth: 84
            }
        }

        RosterList {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

            listModel: rosterListModel
        }
    }
}

