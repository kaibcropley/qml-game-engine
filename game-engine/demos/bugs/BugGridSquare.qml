import QtQuick 2.0
import "qrc:/grid-game/"

GridSquare {
    id: square

    property bool containsFood: false

    Image {
        visible: containsFood
        anchors.centerIn: parent
        width: parent.width / 2
        height: parent.height / 3
        scale: Qt.KeepAspectRatio
        fillMode: Image.PreserveAspectFit
        source: "./images/berry-bush.png"
    }
}
