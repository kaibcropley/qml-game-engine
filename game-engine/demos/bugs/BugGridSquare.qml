import QtQuick 2.0
import "qrc:/grid-game/"

GridSquare {
    id: square
    width: 50
    height: 50

    property bool containsWater: gridPos === "QPoint(4, 4)" // !movementAllowed // false
    property bool containsFood: false
    debug: true

    Image {
        visible: containsFood
        anchors.centerIn: parent
        width: parent.width / 2
        height: parent.height / 3
        scale: Qt.KeepAspectRatio
        fillMode: Image.PreserveAspectFit
        source: "./images/berry-bush.png"
    }

    Image {
        visible: !movementAllowed
        anchors.centerIn: parent
        width: parent.width / 4
        height: width
        source: "../images/stone-single.png"
    }

    Rectangle {
        visible: containsWater
        anchors.centerIn: parent
        width: parent.width * .66
        height: parent.height * .66
        radius: parent.width / 2
        color: "lightblue"
    }
}
