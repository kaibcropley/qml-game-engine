import QtQuick 2.5
import "qrc:/"

CircleCollider {
    id: chain
    height: 30
    width: 30
    color: "lightgreen"
    x: 150
    y: 150
    focus: true

    Component.onCompleted: {
        console.log("chain completed");
        x = 250;
        y = 250;
//        collisionManager.rectanglesCollide(chain.getTopLeftCoordinates(),testBox.getTopLeftCoordinates(),
//                                     chain.getBotRightCoordinates(), testBox.getBotRightCoordinates());
    }

    function stop() {
        chain.x = chain.x
        chain.y = chain.y

        var moveAwayAmount = 2;

        if (chain.movingUp) {
            if (chain.movingUp) {
                chain.y -= moveAwayAmount
            } else if (chain.movingDown) {
                chain.y += moveAwayAmount
            }

            if (chain.movingLeft) {
                chain.x += moveAwayAmount
            } else if (chain.movingRight) {
                chain.x -= moveAwayAmount
            }
        }
    }

    property int velocity: 100
    Behavior on x {
        id: xBehavior
        SmoothedAnimation {
            id: xAnimation;
            velocity: chain.velocity
        }
    }

    Behavior on y {
        id: yBehavior
        SmoothedAnimation {
            id: yAnimation
            velocity: chain.velocity
        }
    }


    Timer {
        interval: 10
        repeat: true // Always attempt to repeat movement
        running:  chain.movingUp || chain.movingDown || chain.movingLeft || chain.movingRight // Always be checking if movement is requested

        property int maxX: 480
        property int maxY: 640

        onTriggered: {
            var dx = 0; // Change in X
            var dy = 0; // Change in Y

            if (chain.movingLeft) {
                dx = -chain.movementAmount;
            } else if (chain.movingRight) {
                dx = chain.movementAmount;
            }

            if (chain.movingUp) {
                dy = -chain.movementAmount;
            } else if (chain.movingDown) {
                dy = chain.movementAmount;
            }

//                var chainColliders = [topWall, botWall, rightWall, leftWall, testBox]
            var chainCenter = chain.getCenterCoordinates();
            var presumedCenterX = chainCenter.x + dx;
            var presumedCenterY = chainCenter.y + dy;
//                for (var i = 0; i < chainColliders.length; i++) {
//                    if (CollisionManager.circleWillCollide(Qt.point(presumedCenterX, presumedCenterY), chain.radius, chainColliders[i])) {
//                        console.log("Can't move there");
//                        return;
//                    }
//                }
            chain.x += dx;
            chain.y += dy;
        }
    }

    property int movementAmount: 2

    Keys.onUpPressed: {
        movingUp = true;
        movingDown = false;
    }

    Keys.onDownPressed: {
        movingDown = true;
        movingUp = false;
    }


    Keys.onRightPressed: {
        movingRight = true;
        movingLeft = false;
    }

    Keys.onLeftPressed: {
        movingRight = false;
        movingLeft = true;
    }

    Keys.onReleased: {
        if (event.isAutoRepeat)
            return ;
        if(event.key == Qt.Key_Left){
            movingLeft = false
        }
        if(event.key == Qt.Key_Right){
            movingRight = false
        }
        if(event.key == Qt.Key_Up){
            movingUp = false
        }
        if(event.key == Qt.Key_Down){
            movingDown = false
        }
    }

    property bool movingUp: false
    property bool movingDown: false
    property bool movingLeft: false
    property bool movingRight: false
}
