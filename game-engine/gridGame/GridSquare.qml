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

        color: ground.state === "dirt" ? "orange" : "lightgreen"

        Rectangle {
            id: fruit
            width: parent.width / 3
            height: width
            color: "darkred"
            anchors.centerIn: parent
            radius: width / 2

            visible: modelData.containsFood
        }

        Rectangle {
            id: rock
            width: parent.width / 3
            height: width
            color: "black"
            anchors.centerIn: parent
            radius: width / 2

            visible: modelData.blocked
        }

        Text {
            anchors.centerIn: parent
            text: index
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
