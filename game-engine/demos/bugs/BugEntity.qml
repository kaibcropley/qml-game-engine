import QtQuick 2.0
import "qrc:/grid-game/"

AnimatedGridEntity {
    id: bug

    property int bugType: 0
    property bool walking:false
    property bool dying: false

    spriteSource: "./images/Little Alchemist Lab BugsSpriteSheet.png"
    spriteFrameWidth: 32
    spriteFrameHeight: 32
    spriteFrameCount:  walking ? 8 : (dying ? 4 : (bugType % 2 === 0 ? 3 : 1))
    spriteFrameDuration: 200
    spriteFrameX: walking ? (spriteFrameWidth * 4) : (dying ? (spriteFrameWidth * 13) : 0)
    spriteFrameY: spriteFrameHeight * bugType

    width: 50
    height: 50

    rotation: lastDirection;

    onMovementStopped: {
        var currSquare = gameGrid.getSquare(gridPos);
        if (currSquare.containsFood) {
            currSquare.containsFood = false;
        }
    }
}
