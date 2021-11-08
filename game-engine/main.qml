import QtQuick 2.6
import QtQuick.Window 2.2
//import "qrc:/demos/bugs/"
//import "qrc:/physics-game/"
//import "qrc:/physics-game/colliders/"
import "qrc:/demos/space-fighter/"
//import kcropley.grid 1.0
//import kcropley.physics 1.0

Window {
    id: rootWindow
    visible: true
    width: 1000
    height: 1000
    title: qsTr("QML Game Engine")

//    BugGame {
//        anchors.fill: parent
//    }


    SpaceFighterGame {
        anchors.fill: parent
    }




//    property int wallsThickness: 30

//    Wall {
//        id: leftWall
//        height: parent.height
//        thickness: wallsThickness

//        x: 0
//        y: 0
//    }

//    Wall {
//        id: rightWall
//        height: parent.height
//        thickness: wallsThickness

//        x: parent.width - width
//        y: 0
//    }

//    Wall {
//        id: topWall
//        width: parent.width
//        thickness: wallsThickness

//        x: 0
//        y: 0
//    }

//    Wall {
//        id: botWall
//        width: parent.width
//        thickness: wallsThickness

//        x: 0
//        y: parent.height - height
//    }

////    SmoothMovementPlayer {
////        width: 50
////        height: 50

////        x: 100
////        y: 100

////        color: "black"

////        possibleMovementCollisions: [ leftWall, rightWall, topWall, botWall ]
////    }

//    property var entities: [ collider, collider2 ]

//    MouseArea {
//        anchors.fill: parent
//        acceptedButtons: Qt.LeftButton | Qt.RightButton

//        onClicked: {
//            var component = Qt.createComponent("qrc:/physics-game/colliders/CircleCollider.qml");
//            var collider = component.createObject(rootWindow, {
//                                                 "x": mouseX - 25,
//                                                 "y": mouseY - 25,
//                                                 "width": 50,
//                                                 "height": 50
//                                             });

//            var copy = entities;
//            copy.push(collider);
//            entities = copy;

//            if (collider === null) {
//                // Error Handling
//                console.log("Error creating collider");
//            }
//        }
//    }

//    Timer {
//        interval: 100
//        repeat: true
//        running: true

//        onTriggered: {
//            var colliding = false;
//            var skip = [];

//            for (var i = 0; i < entities.length; i++)  {
////                if (skip.indexOf(i) !== -1) {
////                    continue;
////                }

//                colliding = false;
//                entities[i].resetForce();
//                for (var x = 0; x < entities.length; x++)  {
//                    if (i != x && collisionManager.circlesCollide(getCenter(entities[i]), entities[i].radius, getCenter(entities[x]), entities[x].radius)) {
//                        colliding = true;
//                        skip.push(x);
//                        entities[i].resolveCollision(entities[x]);
////                        entities[i].calculateVelocity();
//                        entities[i].updatePosition();
//                        break;
//                    }
//                }
//                if (colliding) {
//                    continue;
//                }

//                if (!(entities[i].y > rootWindow.height - 200)) { //botWall.y - (entities[i].height))) {
//                    entities[i].applyForce(Qt.vector2d(0, 1));
//                } else {
//                    entities[i].resetVelocity();
//                }

//                entities[i].calculateVelocity();
//                entities[i].updatePosition();
//            }
//        }
//    }
//    function getCenter(target) {
//        return Qt.point((target.x + (target.width / 2)), (target.y + (target.height/ 2)));
//    }

//    Collider {
//        id: collider
//        width: 50
//        height: 50

//        x: 300
//        y: 400

//        property alias radius: innerRect.radius

//        Rectangle {
//            id: innerRect
//            anchors.fill: parent
//            radius: width / 2
//            color: "lightgreen"
//        }

//        Controller {
//            focus: true
//            onMoveLeft: {
//                console.log("onMoveLeft");
//                collider.applyForce(Qt.vector2d(-2, 0));
//                collider.calculateVelocity();
//            }

//            onMoveRight: {
//                console.log("onMoveRight");
//                collider.applyForce(Qt.vector2d(2, 0));
//                collider.calculateVelocity();
//            }
//        }

//        Behavior on x {
//            id: xBehavior
//            SmoothedAnimation {
//                id: xAnimation;
////                velocity: entity.velocity
//                reversingMode: SmoothedAnimation.Immediate
//            }
//        }

//        Behavior on y {
//            id: yBehavior
//            SmoothedAnimation {
//                id: yAnimation
////                velocity: entity.velocity
//                reversingMode: SmoothedAnimation.Immediate
//            }
//        }
//    }

//    Collider {
//        id: collider2
//        width: 50
//        height: 50
//        x: 400
//        y: 400

//        property alias radius: innerRect2.radius

//        Rectangle {
//            id: innerRect2
//            anchors.fill: parent
//            radius: width / 2
//            color: "lightblue"
//        }
//    }
}
