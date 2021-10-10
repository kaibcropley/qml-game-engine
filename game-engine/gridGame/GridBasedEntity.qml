import QtQuick 2.5
import "qrc:/"
import "qrc:/colliders/"

CircleCollider {
    id: entity

    // Change in x or y for each movement
    property int dx: 100
    property int dy: 100

    // Speed
    property int velocity: 200

    // Movement configs
    property bool movementEnabled: true
    property alias movementDelay: movementDelayTimer.interval
    property bool teleport: false // Disables smoothed movement and teleports player

    // Enable/Disable movement on axis
    property bool horizontalMovementEnabled: movementEnabled
    property bool verticalMovementEnabled: movementEnabled

    // Enable/Disable movement on direction
    property bool leftMovementEnabled: horizontalMovementEnabled
    property bool rightMovementEnabled: horizontalMovementEnabled
    property bool upMovementEnabled: verticalMovementEnabled
    property bool downMovementEnabled: verticalMovementEnabled

    // Believed position within grid
    property int gridX
    property int gridY

    signal movementStarted()
    signal movementStopped()

    // Smooths out movement between changes in x
    Behavior on x {
        id: xBehavior
        enabled: !teleport
        SmoothedAnimation {
            id: xAnimation
            velocity: entity.velocity;
            onRunningChanged: {
                if (running) {
                    movementStarted();
                } else {
                    movementStopped();
                }
            }
        }
    }

    // Smooths out movement between changes in y
    Behavior on y {
        id: yBehavior
        enabled: !teleport
        SmoothedAnimation {
            id: yAnimation
            velocity: entity.velocity
            onRunningChanged: {
                if (running) {
                    movementStarted();
                } else {
                    movementStopped();
                }
            }
        }
    }

    // Forces a delay between player movements
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
            movementEnabled = false;
            movementDelayTimer.restart();
        }
    }
}
