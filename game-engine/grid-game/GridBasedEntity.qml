import QtQuick 2.5
import kcropley.grid 1.0

GridEntity {
    id: entity

    // Change in x or y for each movement
    property int xWidth: 100
    property int yHeight: 100

    x: (gridPos.x * xWidth) + ((100 - width) / 2) // + 25
    y: (gridPos.y * yHeight)  + ((100 - height) / 2) //+ 25

    // Speed
    property int velocity: 200
    property int maxDuration: 300

    // Movement configs
//    property bool movementEnabled: true
//    property alias movementDelay: movementDelayTimer.interval
    property bool teleport: false // Disables smoothed movement and teleports player

    // Movement signals
    signal movementStarted()
    signal movementStopped()

    Component.onCompleted: {
        entityManager.registerEntity(entity);
    }

    // Smooths out movement between changes in x
    Behavior on x {
        id: xBehavior
        enabled: !teleport
        SmoothedAnimation {
            id: xAnimation
            velocity: entity.velocity;
            duration: entity.maxDuration
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
            duration: entity.maxDuration
            onRunningChanged: {
                if (running) {
                    movementStarted();
                } else {
                    movementStopped();
                }
            }
        }
    }
}
