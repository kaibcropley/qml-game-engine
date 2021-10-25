import QtQuick 2.5
import kcropley.grid 1.0

Grid {
    id: gameGrid

    property int squareWidth: 100
    property int squareHeight: 100

    property alias model: gridRepeater.model
    property alias delegate: gridRepeater.delegate

    function getSquare(gridPos) {
        return gridRepeater.itemAt((gridPos.y * gameGrid.rows) + gridPos.x)
    }

    Repeater {
        id: gridRepeater
    }
}
