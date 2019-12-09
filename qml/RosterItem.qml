import QtQuick 2.0
import QtQuick.Controls 1.6

Rectangle {
    property string firstName
    property string lastName

    id: rectangle
    //implicitHeight: text.height
    width: listView.width
    height: 50
    color: "grey"
    border.color: "black"
    radius: 5

    Rectangle {
        id : itemCircle
        width: 32
        height: width
        color: model.avatarColor
        radius: width * 0.5
        anchors.verticalCenterOffset: 0
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
    }

    Text {
        x: 45
        y: 0
        width: 209
        height: 32
        text: firstName + "\n" + lastName
        verticalAlignment: Text.AlignVCenter
        font.family: "Times New Roman"
        font.bold: true
        font.pointSize: 10
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: itemCircle.right
        renderType: Text.NativeRendering
    }
}
