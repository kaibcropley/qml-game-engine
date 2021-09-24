import QtQuick 2.6
import QtQuick.Window 2.2

Window {
    id: rootWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    property bool collisionsRunning: true

    Wall {
        id: leftWall
        height: parent.height

        x: 0
        y: 0
    }

    Wall {
        id: rightWall
        height: parent.height

        x: rootWindow.width - width
        y: 0
    }

    Wall {
        id: topWall
        width: parent.width

        x: 0
        y: 0
    }

    Wall {
        id: botWall
        width: parent.width

        x: 0
        y: rootWindow.height - height
    }

    Timer {
        id: collisionManager
        interval: 1000 // (1/100 of a second)
        triggeredOnStart: false
        repeat: collisionsRunning

        // TODO optimzation
        property variant chainColliders: [topWall, botWall, rightWall, leftWall, testBox]

        Component.onCompleted: {
            if (collisionsRunning) {
//                start();
            }
        }

        // TODO move to another thread
        onTriggered: {
            for (var i = 0; i < chainColliders.length; i++) {
                if (chain.isTouchingRect(chainColliders[i])) {
//                    chain.stop();
                }
            }
        }
    }

//    function pointsColliding()



    // Spin rect w/ mouse drag
//    MouseArea{
//        id: mouseArea
//        anchors.fill: background;
//        onPositionChanged:  {
//            var point = mouseArea.mapToItem(background, mouse.x, mouse.y);
//            console.log("point:", point);
//            var diffX = (point.x - background.centerX);
//            var diffY = -1 * (point.y - background.centerY);
//            var rad = Math.atan (diffY / diffX);
//            var deg = (rad * 180 / Math.PI);
//            if (diffX > 0 && diffY > 0) {
//                rect.rotation = 90 - Math.abs (deg);
//            }
//            else if (diffX > 0 && diffY < 0) {
//                rect.rotation = 90 + Math.abs (deg);
//            }
//            else if (diffX < 0 && diffY > 0) {
//                rect.rotation = 270 + Math.abs (deg);
//            }
//            else if (diffX < 0 && diffY < 0) {
//                rect.rotation = 270 - Math.abs (deg);
//            }
//        }
//    }

    // Stretcher
//    MouseArea{
//        id: mouseArea
//        anchors.fill: background;
//        onPositionChanged:  {
//            var point = mouseArea.mapToItem(background, mouse.x, mouse.y);
//            console.log("point:", point);
//            var diffX = (point.x - background.centerX);
//            var diffY = -1 * (point.y - background.centerY);
//            var rad = Math.atan (diffY / diffX);
//            var deg = (rad * 180 / Math.PI);
//            if (diffX > 0 && diffY > 0) {
//                rect.rotation = 90 - Math.abs (deg);
//            }
//            else if (diffX > 0 && diffY < 0) {
//                rect.rotation = 90 + Math.abs (deg);
//            }
//            else if (diffX < 0 && diffY > 0) {
//                rect.rotation = 270 + Math.abs (deg);
//            }
//            else if (diffX < 0 && diffY < 0) {
//                rect.rotation = 270 - Math.abs (deg);
//            }
//            rect.height = Math.sqrt((diffX * diffX) + (diffY * diffY)) * 2;
//        }
//    }

    function shapesCollide(shapeA, shapeB) {
        if (shapeA.colliderRectangle) {
            return rectangleWillCollide(shapeA.getTopLeftCoordinate(), shapeA.getBotRightCoordinate(), shapeB);
        } else {
            return circleWillCollide(shapeA.getCenterCoordinates(), shapeA.radius, shapeB);
        }
    }

    function rectanglesCollide(rectAPoint1, rectAPoint2, rectBPoint1, rectBPoint2) {
        return (rectAPoint1.x < rectBPoint2.x &&
                rectBPoint1.x < rectAPoint2.x &&
                rectAPoint1.y < rectBPoint2.y &&
                rectBPoint1.y < rectAPoint2.y);
    }


    function circlesCollide(aCenter, aRadius, bPoint, bRadius) {
        return distanceBetweenCircles(aCenter, bPoint) < aRadius + bRadius;
    }

    function distanceBetweenCircles(aCenter, bPoint) {
        var dx = aCenter.x - bPoint.x;
        var dy = aCenter.y - bPoint.y;
        return Math.sqrt(dx * dx + dy * dy);
    }

    // From https://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection
    // User e.James - https://stackoverflow.com/users/33686/e-james
    function circleAndRectangleCollide(cirCenter, cirRadius, rectCenter, rectWidth, rectHeight) {
        var circleDistanceX = Math.abs(cirCenter.x - rectCenter.x);
        var circleDistanceY = Math.abs(cirCenter.y - rectCenter.y);

        if (circleDistanceX > (rectWidth/2 + cirRadius)) { return false; }
        if (circleDistanceY > (rectHeight/2 + cirRadius)) { return false; }

        if (circleDistanceX <= (rectWidth/2)) { return true; }
        if (circleDistanceY <= (rectHeight/2)) { return true; }

        var cornerDistance_sq = (circleDistanceX - rectWidth/2)^2 +
                             (circleDistanceY - rectHeight/2)^2;

        return (cornerDistance_sq <= (cirRadius^2));
    }

    function circleWillCollide(cirCenter, cirRadius, otherShape) {
        if (otherShape.colliderRectangle) { // Circle && Rect
            return circleAndRectangleCollide(cirCenter, cirRadius, otherShape.getCenterCoordinates(), otherShape.width, otherShape.height);
        } else { // Circle && Circle
            return circlesCollide(cirCenter, cirRadius, otherShape.getCenterCoordinates(), otherShape.radius);
        }
    }

    function rectangleWillCollide(rectPoint1, rectPoint2, otherShape) {
        if (otherShape.colliderRectangle) { // Rect && Rect
            return rectanglesCollide(rectPoint1, rectPoint2, otherShape.getTopLeftCoordinates(), otherShape.getBotRightCoordinates());
        } else { // Rect && Circle
            return circleAndRectangleCollide(otherShape.getCenterCoordinates(), otherShape.radius, getRectangleCenterCoordinates(rectPoint1, rectPoint2), Math.abs(rectPoint1.x - rectPoint2.x), Math.abs(rectPoint1.y - rectPoint1.y));
        }
    }

    function getRectangleCenterCoordinates(rectPoint1, rectPoint2) {
        return Qt.point((rectPoint1.x + rectPoint2.x) / 2, (rectPoint1.y + rectPoint1.y) / 2);
    }

//    RectangleCollider {
    CircleCollider {
        id: chain
        height: 30
        width: 30
        color: "lightgreen"
        x: 150
        y: 150
        focus: true

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

        property int velocity: 400
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

                var chainColliders = [topWall, botWall, rightWall, leftWall, testBox]
                var chainCenter = chain.getCenterCoordinates();
                var presumedCenterX = chainCenter.x + dx;
                var presumedCenterY = chainCenter.y + dy;
                for (var i = 0; i < chainColliders.length; i++) {
                    if (circleWillCollide(Qt.point(presumedCenterX, presumedCenterY), chain.radius, chainColliders[i])) {
                        console.log("Can't move there");
                        return;
                    }
                }
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



//    RectangleCollider {
//            id: rect
//            width: 50; height: 50
//            color: "lightgreen"


//            y: parent.height / 2

//            MouseArea {
//                anchors.fill: parent
//                drag.target: rect
//                drag.axis: Drag.XAndYAxis
//                drag.minimumX: 0
//                drag.maximumX: rootWindow.width - rect.width
//            }
////            Behavior on x { SmoothedAnimation { velocity: 100 } }
////            Behavior on y { SmoothedAnimation { velocity: 100 } }
////            Keys.onRightPressed: rect.x = rect.x + 20
////            Keys.onLeftPressed: rect.x = rect.x - 20
////            Keys.onUpPressed: {
////                yMovementAnimation.startAnimation(false);
////            }

////            Keys.onDownPressed: {
////                yMovementAnimation.startAnimation(true);
////            }

//            property int movementAmount: 2000

////            Keys.onRightPressed: {
////                xMovementAnimation.startAnimation(true);
////            }

////            Keys.onLeftPressed: {
////                xMovementAnimation.startAnimation(false);
////            }

//            Keys.onReleased: {

//                if (event.isAutoRepeat)
//                    return ;
//                if(event.key == Qt.Key_Left){
//                    console.log("Released left key");
//                    xMovementAnimation.stop();
//                }
//                if(event.key == Qt.Key_Right){
//                    console.log("Released right key");
//                    xMovementAnimation.stop();
//                }
//                if(event.key == Qt.Key_Up){
//                    yMovementAnimation.stop();
//                }
//                if(event.key == Qt.Key_Down){
//                    yMovementAnimation.stop();
//                }


//            }

////            Timer {
////                id: collisionManager
////                interval: 1000 / 60 // (1/60 of a second)
////                triggeredOnStart: false
////                repeat: collisionsRunning

////                Component.onCompleted: {
////                    if (collisionsRunning) {
////                        start();
////                    }
////                }

////                onTriggered: {
////                    if (rect.isTouchingRect(testBox)) {
////                        console.log("Touching!");
////                        xMovementAnimation.stop();
////                    }
////                }
////            }

//            MovementAnimation {
//                id: xMovementAnimation

//                movementSpeed: rect.movementAmount
//                moveX: true

//                target: rect

//                onStarted: {
//                    console.log("xMovementAnimation started");
//                }

//                onStopped: {
//                    console.log("xMovementAnimation stopped");
//                }
//            }

//            MovementAnimation {
//                id: yMovementAnimation

//                movementSpeed: rect.movementAmount
//                moveX: false

//                target: rect
//            }
//        }

    CircleCollider {
        id: testBox
        anchors.centerIn: parent
        color: "lightblue"
        width: 50
        height: 50
    }

    function getRandomInt(min, max) {
        min = Math.ceil(min);
        max = Math.floor(max);
        return Math.floor(Math.random() * (max - min + 1)) + min;
    }
}
