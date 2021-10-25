import QtQuick 2.5
import "qrc:/colliders/"

CircleCollider {
    id: entity

    property bool movingUp: false
    property bool movingDown: false
    property bool movingLeft: false
    property bool movingRight: false

    property bool collisionsEnabled: true
    property var possibleMovementCollisions: []

    property int velocity: 100
    property int movementAmount: 10

    Behavior on x {
        id: xBehavior
        SmoothedAnimation {
            id: xAnimation;
            velocity: entity.velocity
            reversingMode: SmoothedAnimation.Immediate
        }
    }

    Behavior on y {
        id: yBehavior
        SmoothedAnimation {
            id: yAnimation
            velocity: entity.velocity
            reversingMode: SmoothedAnimation.Immediate
        }
    }

    Timer {
        interval: 10
        repeat: true // Always attempt to repeat movement
        running: entity.movingUp || entity.movingDown || entity.movingLeft || entity.movingRight // Always be checking if movement is requested

        onTriggered: {
            var dx = 0; // Change in X
            var dy = 0; // Change in Y

            if (entity.movingLeft) {
                dx = -entity.movementAmount;
            } else if (entity.movingRight) {
                dx = entity.movementAmount;
            }

            if (entity.movingUp) {
                dy = -entity.movementAmount;
            } else if (entity.movingDown) {
                dy = entity.movementAmount;
            }

            if (collisionsEnabled) {
                var playerCenter = entity.getCenterCoordinates();
                var presumedCenterX = playerCenter.x + dx;
                var presumedCenterY = playerCenter.y + dy;

                for (var i = 0; i < possibleMovementCollisions.length; i++) {
                    if (possibleMovementCollisions[i].colliderRectangle) { // Cir collide w/ Rect
                        if (collisionManager.circleAndRectangleCollide(Qt.point(presumedCenterX, presumedCenterY), entity.radius, possibleMovementCollisions[i].getCenterCoordinates(), possibleMovementCollisions[i].width, possibleMovementCollisions[i].height)) {
                            return;
                        }
                    } else { // Cir collide w/ Cir
                        if (collisionManager.circlesCollide(Qt.point(presumedCenterX, presumedCenterY), entity.radius, possibleMovementCollisions[i].getCenterCoordinates(), playerColliders[i].radius)) {
                            return;
                        }
                    }
                }
            }

            // If we aren't about to collide with something, make move
            entity.x += dx;
            entity.y += dy;
        }
    }
}
