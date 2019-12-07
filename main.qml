import QtQuick 2.13
import QtQuick.Window 2.13
import App 1.0
import QtQuick.Layouts 1.0

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ColumnLayout {
        id: columnLayout
        spacing: 10
        anchors.fill: parent

        RowLayout {
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.right: parent.right
            anchors.rightMargin: 5

            Text {
                id: element
                text: qsTr("Filter:")
                Layout.preferredHeight: 31
                Layout.preferredWidth: 87
                styleColor: "#c9a1a1"
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                fontSizeMode: Text.Fit
                renderType: Text.NativeRendering
                font.pixelSize: 12
            }

            TextEdit {
                id: textEdit
                text: qsTr("*")
                Layout.preferredHeight: 20
                Layout.preferredWidth: 360
                transformOrigin: Item.Center
                font.pixelSize: 12
            }

            Rectangle {
                id: rectangle
                width: 77
                height: 44
                color: "#ebb6b6"
                radius: 10

                Text {
                    id: element1
                    text: qsTr("Apply")
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.fill: parent
                    font.pixelSize: 12
                }
            }
        }

        ListView {
            id: listView
            visible: true
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            spacing : 10
            model: RosterListModel {}
            clip: true

            delegate: Rectangle {
                //implicitHeight: text.height
                width: listView.width
                height: 60
                color: "grey"
                border.color: "black"
                radius: 10

                Row
                {
                    anchors.margins: 5
                    anchors.fill: parent

                    Rectangle {
                        anchors.verticalCenter: parent.verticalCenter
                        width: 32
                        height: width
                        color: model.avatarColor
                        radius: width * 0.5
                    }

                    Text {
                        anchors.centerIn: parent
                        renderType: Text.NativeRendering
                        text: model.firstName + " " + model.lastName
                    }
                }
            }
        }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
