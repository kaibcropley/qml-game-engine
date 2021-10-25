import QtQuick 2.0
import kcropley.grid 1.0

Item {
    id: gridSquare

    property alias background: ground

    property bool debug: false

    property bool containsFood: modelData.containsFood
    property bool blocked: modelData.blocked

    Rectangle {
        id: ground

        border.color: "black"
        border.width: 3

        anchors.fill: parent

//        state: modelData.squareType === 0 ? "dirt" : "grass"

        Image {
            anchors.fill: parent
//            source: "../images/Grass 00" + (modelData.squareType + 1) + ".png"
            source: "../demos/bugs/images/dirt.png"
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
            visible: containsFood //modelData.containsFood
            anchors.centerIn: parent
            width: parent.width / 2
            height: parent.height / 3
            scale: Qt.KeepAspectRatio
            fillMode: Image.PreserveAspectFit
            source: "../demos/bugs/images/berry-bush.png"
        }

        Image {
            visible: blocked
            anchors.centerIn: parent
            width: parent.width / 4
            height: width
            source: "../demos/images/stone-single.png"
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
