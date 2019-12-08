import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.6
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles.Desktop 1.0

import App 1.0

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Display Roster")

    Timer {
        id: modelUpdate
        interval: 2000;
        repeat: true
        running: true
        triggeredOnStart: true

        onTriggered: {

        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        x: 0
        y: 0

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

        RosterListModel {
            id : rosterModel
        }

        ListView {
            id: listView
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            visible: true
            spacing : 10
            model: rosterModel
            clip: true

            delegate: RosterItem {}
        }
    }
}

/*##^##
Designer {
    D{i:2;anchors_x:53;anchors_y:16}
}
##^##*/
