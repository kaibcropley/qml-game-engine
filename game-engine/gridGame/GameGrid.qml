import QtQuick 2.5

Grid {
    id: gameGrid

    property int squareWidth: 100
    property int squareHeight: 100

    function eatFruit(gridX, gridY) {
        var square = getSquare(gridX, gridY);
        if (square !== null && square.state === "fruit") {
            square.state = "grass";
            return true; // Indicate that fruit was eaten
        }
        return false; // Indicate no fruit was eaten
    }

    // Returns requested square from repeater
    //  Returns null if no square found
    function getSquare(gridX, gridY) {
        return gridRepeater.itemAt((gridY * gameGrid.rows) + gridX)
    }

    Repeater {
        id: gridRepeater
        Component.onCompleted: {
            var newModel = [];
            for (var i=0; i < 100; i++) {
                if (i % 10 === 0 || i % 10 === 9) {
                    newModel[i] = "dirt";
                } else if (i % 5 === 0) {
                    newModel[i] = "fruit";
                } else {
                    newModel[i] = "grass";
                }
            }
            model = newModel;
        }

        delegate: Rectangle {
            id: ground
            property int gridX: index % gameGrid.columns
            property int gridY: index / gameGrid.columns

            border.color: "black"
            border.width: 3
            width: squareWidth
            height: squareHeight

            state: modelData

            color: ground.state === "dirt" ? "orange" : "lightgreen"

            Rectangle {
                id: fruit
                width: parent.width / 3
                height: width
                color: "darkred"
                anchors.centerIn: parent
                radius: width / 2

                visible: ground.state === "fruit"
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
                },
                State {
                    name: "fruit"
                }
            ]
        }
    }
}
