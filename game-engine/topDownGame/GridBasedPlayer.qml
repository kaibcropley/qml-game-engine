import QtQuick 2.5
import "qrc:/"

CircleCollider {
    id: girdPlayer

    // Change in x or y for each movement
    property int dx: 10
    property int dy: 10

    // Movement configs
    property bool movementEnabled: true
    property alias movementDelay: movementDelayTimer.interval
    property bool teleport: false // Disables smoothed movement and teleports player
    property int velocity: 200

    // Smooths out movement between changes in x
    Behavior on x {
        id: xBehavior
        enabled: !teleport
        SmoothedAnimation { velocity: girdPlayer.velocity }
    }

    // Smooths out movement between changes in y
    Behavior on y {
        id: yBehavior
        enabled: !teleport
        SmoothedAnimation { velocity: girdPlayer.velocity }
    }

    Timer {
        id: movementDelayTimer
        interval: 0 // Set interval default to 0 to ensure it only triggers if the caller sets movementDelay

        onTriggered: {
            movementEnabled = true;
        }
    }

    // Arrow keys are used as movement
    Keys.onRightPressed: {
        if (movementEnabled) {
            x += dx;
            checkMovementDelay();
        }
    }

    Keys.onLeftPressed: {
        if (movementEnabled) {
            x -= dx;
            checkMovementDelay();
        }
    }

    Keys.onUpPressed: {
        if (movementEnabled) {
            y -= dy;
            checkMovementDelay();
        }
    }

    Keys.onDownPressed: {
        if (movementEnabled) {
            y += dy;
            checkMovementDelay();
        }
    }

    function checkMovementDelay() {
        if (movementDelay > 0) {
            movementEnabled = false;
            movementDelayTimer.restart();
        }
    }
}
