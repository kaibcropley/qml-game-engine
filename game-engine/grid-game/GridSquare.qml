import QtQuick 2.0
import kcropley.grid 1.0

GridSquareData {
    id: gridSquare

    Rectangle {
        border.color: "black"
        border.width: 3
    }

    Component.onCompleted: {
        gridMatrix.setSquare(gridSquare);
    }

    property bool debug: false

//    property string gridPos
//    property bool movementAllowed: true
    property alias backgroundSource: imageBackground.source;

    Image {
        id: imageBackground
        anchors.fill: parent
    }

    Text {
        visible: debug
        anchors {
            top: parent.top
            right: parent.right
            margins: 5
        }

        text: gridPos.toString();
    }
}
