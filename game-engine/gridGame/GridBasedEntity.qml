import QtQuick 2.5
import kcropley.grid 1.0
import "qrc:/"
import "qrc:/colliders/"

GridEntity {
    id: entity

//    GridEntity {
//        id: gridEntity
//    }

//    property alias gridEntity: gridEntity

    // Position within grid

    // Change in x or y for each movement
    property int xWidth: 100
    property int yHeight: 100

    x: (gridPos.x * xWidth) + 25
    y: (gridPos.y * yHeight) + 25

    // Speed
    property int velocity: 200
    property int maxDuration: 300

    // Movement configs
    property bool movementEnabled: true
//    property alias movementDelay: movementDelayTimer.interval
    property bool teleport: false // Disables smoothed movement and teleports player

    // Movement signals
    signal movementStarted()
    signal movementStopped()

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
