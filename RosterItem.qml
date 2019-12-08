import QtQuick 2.0
import QtQuick.Controls 1.6


Rectangle {
    id: rectangle
    //implicitHeight: text.height
    width: listView.width
    height: 50
    color: "grey"
    border.color: "black"
    radius: 5

    Rectangle {
        width: 32
        height: width
        color: model.avatarColor
        radius: width * 0.5
    }

    Text {
        x: 45
        y: 0
        width: 209
        height: 32
        text: "#model.firstName + \"\\n\" + model.lastName#"
        renderType: Text.NativeRendering
    }
}
