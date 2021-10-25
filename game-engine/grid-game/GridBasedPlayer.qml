import QtQuick 2.5
import "qrc:/"

GridBasedEntity {
    id: gridPlayer

    // Enable/Disable movement on axis Note is overwritten by directional enablers
    property bool horizontalMovementEnabled: movementEnabled
    property bool verticalMovementEnabled: movementEnabled

    // Enable/Disable movement on direction
    property bool leftMovementEnabled: horizontalMovementEnabled
    property bool rightMovementEnabled: horizontalMovementEnabled
    property bool upMovementEnabled: verticalMovementEnabled
    property bool downMovementEnabled: verticalMovementEnabled

    Controller {
        focus: true

        onMoveLeft: {
            gridPlayer.moveLeft();
        }

        onMoveRight: {
            gridPlayer.moveRight();
        }

        onMoveUp: {
            gridPlayer.moveUp();
        }

        onMoveDown: {
            gridPlayer.moveDown();
        }
    }

    // Forces a delay between movements
    Timer {
        id: movementDelayTimer
        interval: 0 // Set interval default to 0 to ensure it only triggers if the caller sets movementDelay

        onTriggered: {
            movementEnabled = true;
        }
    }

    function moveLeft() {
        if (leftMovementEnabled && !xAnimation.running) {
            x -= dx;
            gridX--;
            checkMovementDelay();
        }
    }

    function moveRight() {
        if (rightMovementEnabled && !xAnimation.running) {
            x += dx;
            gridX++;
            checkMovementDelay();
        }
    }

    function moveUp() {
        if (upMovementEnabled && !yAnimation.running) {
            y -= dy;
            gridY--;
            checkMovementDelay();
        }
    }

    function moveDown() {
        if (downMovementEnabled && !yAnimation.running) {
            y += dy;
            gridY++;
            checkMovementDelay();
        }
    }

    function checkMovementDelay() {
        if (movementDelay > 0) {
//            movementEnabled = false;
            movementDelayTimer.restart();
        }
    }
}
