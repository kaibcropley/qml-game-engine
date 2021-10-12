import QtQuick 2.5

Grid {
    id: gameGrid

    property int squareWidth: 100
    property int squareHeight: 100

    property alias model: gridRepeater.model

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

        delegate: GridSquare {
            id: square
            width: squareWidth
            height: squareHeight

//            ground.state: modelData.squareType

        }
    }
}
