import QtQuick 2.0
import kcropley.grid 1.0

Item {
    id: gridSquare

    property alias background: ground

    property bool debug: false

    Rectangle {
        id: ground

        border.color: "black"
        border.width: 3

        anchors.fill: parent

//        state: modelData.squareType === 0 ? "dirt" : "grass"

        Image {
            anchors.fill: parent
            source: "../images/Grass 00" + (modelData.squareType + 1) + ".png"
        }

        Text {
            visible: debug
            anchors {
                top: parent.top
                right: parent.right
                margins: 5
            }

            text: modelData.gridPos.toString()
        }

        Image {
            visible: modelData.containsFood
            anchors.centerIn: parent
            width: parent.width / 2
            height: parent.height / 3
            scale: Qt.KeepAspectRatio
            fillMode: Image.PreserveAspectFit
            source: "../images/berry-bush.png"
        }

        Image {
            visible: modelData.blocked
            anchors.centerIn: parent
            width: parent.width / 4
            height: width
            source: "../images/stone-single.png"
        }

        states: [
            State {
                name: "dirt"
            },
            State {
                name: "grass"
            }
        ]
    }
}
