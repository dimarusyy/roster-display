import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0

Popup {
    id: popup
    property alias firstName: firstName.text
    property alias lastName: lastName.text
    property alias userName: userName.text
    property alias sex: sex.text
    property alias country: country.text
    property alias birthday: birthday.text
    property alias language: language.text

    width: 400
    height: 200

    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

    Rectangle {
        id: rectangle
        anchors.fill: parent
        color: "#9a29386c"
        radius: 5
        border.width: 2

        ColumnLayout {
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: layoutDesc.right
            anchors.leftMargin: 10
            Layout.fillHeight: true

            Text {
                id: firstName
                text: "123"
                Layout.fillWidth: true
            }

            Text {
                id: lastName
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                Layout.fillWidth: true
            }

            Text {
                id: userName
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                Layout.fillWidth: true
            }

            Text {
                id: sex
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                Layout.fillWidth: true
            }

            Text {
                id: country
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                Layout.fillWidth: true
            }

            Text {
                id: birthday
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                Layout.fillWidth: true
            }

            Text {
                id: language
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                Layout.fillWidth: true
            }
        }

        ColumnLayout {
            id: layoutDesc

            width: parent.width/2
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            Layout.fillHeight: true

            Text {
                text: "FirstName:"
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.fillWidth: false
            }
            Text {
                text: "LastName:"
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.fillWidth: false
            }
            Text {
                text: "UserName:"
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.fillWidth: false
            }
            Text {
                text: "Sex:"
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.fillWidth: false
            }
            Text {
                text: "Country:"
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.fillWidth: false
            }
            Text {
                text: "Birthday:"
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.fillWidth: false
            }
            Text {
                text: "Language:"
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.fillWidth: false
            }
        }

    }
}


/*##^##
Designer {
    D{i:2;anchors_y:40}D{i:10;anchors_x:0;anchors_y:40}
}
##^##*/
