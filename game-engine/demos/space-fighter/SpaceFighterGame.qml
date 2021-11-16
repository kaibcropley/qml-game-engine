import QtQuick 2.0
import "qrc:/"
import "qrc:/physics-game/colliders/"

Item {

    Component.onCompleted: {
        gameTimer.start();
    }

    MouseArea {
        anchors.fill: parent

        onMouseXChanged: {
            entity.x = mouseX;
        }

        onMouseYChanged: {
            entity.y = mouseY;
        }
    }

    Timer {
        id: gameTimer
        interval: 500
        repeat: true

        onTriggered: {
            if (collisionManager.collision(entity, other)) {
                console.log("Collision!");
            }
        }
    }

    Spaceship {
        id: entity
        width: 50
        height: 50
        imageSource: "./images/spaceships/01/Spaceship_01_RED.png"

        property real angle: rotation
        property real radians: angle * Math.PI/180 // From https://stackoverflow.com/questions/41130615/offset-rotation-for-qml-item

        property bool movingUp: false
        property bool movingDown: false
        property bool movingLeft: false
        property bool movingRight: false

        property bool collisionsEnabled: true
        property var possibleMovementCollisions: []

        property int velocity: 100
        property int movementAmount: 25

        Controller {
            focus: true

            onMoveLeft: {
                entity.movingLeft = true;
                entity.movingRight = false;
            }

            onMoveRight: {
                entity.movingLeft = false;
                entity.movingRight = true;
            }

            onMoveUp: {
                entity.movingUp = true;
                entity.movingDown = false;
            }

            onMoveDown: {
                entity.movingUp = false;
                entity.movingDown = true;
            }

            onStopMovingLeft: {
                entity.movingLeft = false
            }

            onStopMovingRight: {
                entity.movingRight = false
            }

            onStopMovingUp: {
                entity.movingUp = false
            }

            onStopMovingDown: {
                entity.movingDown = false
            }

//            onMoveLeft: {
//                if (moveableEntity.rotation == 0) {
//                    moveableEntity.rotation = 355
//                } else {
//                    moveableEntity.rotation -= 5;
//                }

////                console.log("radians:", moveableEntity.radians);
//            }

//            onMoveUp: {
//                console.log("Up x:", moveableEntity.rotation, Math.sin(moveableEntity.rotation));
//                moveableEntity.x += 5 * Math.sin(moveableEntity.rotation);
//            }

//            onMoveDown: {
//                moveableEntity.x += 5 * -Math.sin(moveableEntity.rotation);
//            }
        }

        Behavior on x {
            id: xBehavior
            SmoothedAnimation {
                id: xAnimation
                velocity: 100
            }
        }

        // Smooths out movement between changes in y
        Behavior on y {
            id: yBehavior
            SmoothedAnimation {
                id: yAnimation
                velocity: 100
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

//                if (entity.collisionsEnabled && entity.possibleMovementCollisions.length > 0) {
//                    var playerCenter = entity.getCenterCoordinates();
//                    var presumedCenterX = playerCenter.x + dx;
//                    var presumedCenterY = playerCenter.y + dy;

//                    for (var i = 0; i < entity.possibleMovementCollisions.length; i++) {
//                        if (entity.possibleMovementCollisions[i].colliderRectangle) { // Cir collide w/ Rect
//                            if (collisionManager.circleAndRectangleCollide(Qt.point(presumedCenterX, presumedCenterY), entity.radius, entity.possibleMovementCollisions[i].getCenterCoordinates(), possibleMovementCollisions[i].width, possibleMovementCollisions[i].height)) {
//                                return;
//                            }
//                        } else { // Cir collide w/ Cir
//                            if (collisionManager.circlesCollide(Qt.point(presumedCenterX, presumedCenterY), entity.radius, entity.possibleMovementCollisions[i].getCenterCoordinates(), playerColliders[i].radius)) {
//                                return;
//                            }
//                        }
//                    }
//                }

                // If we aren't about to collide with something, make move
                entity.x += dx;
                entity.y += dy;
            }
        }
    }

    Rectangle {
        width: 25
        height: 5
        color: "orange"
//        anchors.bottom: moveableEntity.top
//        anchors.horizontalCenter: moveableEntity.horizontalCenter
        transform: Rotation {
                    origin.x: entity.width / 2
                    origin.y: entity.height / 2
                    angle: entity.angle
                }

        onXChanged: {
            console.log("x:", x);
        }
    }

    CircleEntity {
        id: other
        width: 50
        height: 50
        x: 100
        y: 125

        Rectangle {
            id: collision
            anchors.fill: parent
            radius: width / 2
            color: "lightblue"
        }
    }
}
