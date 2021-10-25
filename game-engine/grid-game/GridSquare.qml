import QtQuick 2.0
import kcropley.grid 1.0

Rectangle {
    id: gridSquare
    border.color: "black"
    border.width: 3

    property bool debug: false

    property string gridPos
    property bool movementAllowed: true
    property alias backgroundSource: imageBackground.source;

    Text {
        visible: debug
        anchors {
            top: parent.top
            right: parent.right
            margins: 5
        }

        text: gridPos
    }

    Image {
        id: imageBackground
        anchors.fill: parent
    }

    Image {
        visible: !movementAllowed
        anchors.centerIn: parent
        width: parent.width / 4
        height: width
        source: "../demos/images/stone-single.png"
    }
}
