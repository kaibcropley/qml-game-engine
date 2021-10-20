import QtQuick 2.0
import kcropley.grid 1.0

GridSquareData {
    id: gridSquare

    property alias background: ground



    Component.onCompleted: {
//        console.log(JSON.stringify(modelData))
    }

    Rectangle {
        id: ground

        border.color: "black"
        border.width: 3

        anchors.fill: parent

        state: modelData.squareType === 0 ? "dirt" : "grass"

        Image {
            anchors.fill: parent
            source: "../images/dirt.png" // "../images/stars/Space_Stars8.png"
        }

//        Image {
//            visible: modelData.containsFood
//            anchors.centerIn: parent
//            width: parent.width / 4
//            height: width
//            source: "../images/stars/cartoon-star.png"
//        }

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
