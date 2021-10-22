import QtQuick 2.6
import QtQuick.Window 2.2
import "qrc:/colliders/"
import "qrc:/gridGame/"
import kcropley.grid 1.0
//import "qrc:/cardGame/"
//import "qrc:/CollisionManager.js" as CollisionManager

Window {
    id: rootWindow
    visible: true
    width: 1000
    height: 1000
    title: qsTr("QML Game Engine")

    property bool collisionsRunning: true

    Component.onCompleted: {
//        gameBoard.createRandomizedGameBoard(gameGrid.columns, gameGrid.rows);
        movementTimer.start();
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            var p = Qt.point(Math.ceil(mouseX / 100) - 1, Math.ceil(mouseY / 100) - 1);
            var currSquare = gameGrid.getSquare(p);
            currSquare.containsFood = true;
        }
    }

    Timer {
        id: movementTimer
        interval: 400
        triggeredOnStart: true
        repeat: true

        onTriggered: {
            var entities = [ entity, entity2 ];

            for (var i = 0; i < entities.length; i++)  {
                var currEntity = entities[i];
                if (currEntity.pathHasSteps()) {
                    currEntity.followPath(1);
                } else {
                    var p = findNearestFood(currEntity);
                    if (p !== undefined && p !== null) {
                        currEntity.findPath(p);
                    }
                }
            }
        }

        function getRandomInt(min, max) {
          min = Math.ceil(min);
          max = Math.floor(max);
          return Math.floor(Math.random() * (max - min) + min); //The maximum is exclusive and the minimum is inclusive
        }
    }

    function findNearestFood(targetEntity) {
        var source = targetEntity.gridPos;
        var currTargetFood;
        var currTargetFoodDistance = gameGrid.rows * gameGrid.columns;

        for (var row = 0; row < gameGrid.rows; row++) {
            for (var col = 0; col < gameGrid.columns; col++) {
                var currPoint = Qt.point(row, col);
                if (gameGrid.getSquare(currPoint).containsFood) {
                    var distance = distanceBetween(source, currPoint);
                    if (distance < currTargetFoodDistance) {
                        currTargetFood = currPoint;
                        currTargetFoodDistance = distance;
                    }
                }
            }
        }
        return currTargetFood;
    }

    function distanceBetween(p1, p2) {
        return Math.abs(p1.x - p2.x) + Math.abs(p1.y - p2.y);
    }

    GameGrid {
        id: gameGrid
        columns: 10
        rows: 10
        anchors {
            fill: parent
        }

        Component.onCompleted: {
            model = gridMatrix.matrixToOneDimension();
        }
    }

    BugEntity {
        id: entity
        width: 50
        height: 50

        bugType: 12
        maxDuration: movementTimer.interval

        Component.onCompleted: {
            entityManager.registerEntity(entity);
        }

        onMovementStopped: {
            var currSquare = gameGrid.getSquare(gridPos);
            if (currSquare.containsFood) {
                currSquare.containsFood = false;
            }
        }
    }

    BugEntity {
        id: entity2
        width: 50
        height: 50

        bugType: 1
        maxDuration: movementTimer.interval

        gridPos: Qt.point(4, 9)

        Component.onCompleted: {
            entityManager.registerEntity(entity2);
        }

        onMovementStopped: {
            var currSquare = gameGrid.getSquare(gridPos);
            if (currSquare.containsFood) {
                currSquare.containsFood = false;
            }
        }
    }




//    CircleCollider {
//        id: entity
//        width: 30
//        height: width
//        color: "lightgreen"
//        focus: true

//        property bool movingUp: false
//        property bool movingDown: false
//        property bool movingLeft: false
//        property bool movingRight: false

//        property int velocity: 200

//        Behavior on x {
//            id: xBehavior
//            SmoothedAnimation {
//                id: xAnimation;
//                velocity: entity.velocity
//                reversingMode: SmoothedAnimation.Immediate
//                maximumEasingTime: 1000
//            }
//        }

//        Behavior on y {
//            id: yBehavior
//            SmoothedAnimation {
//                id: yAnimation
//                velocity: entity.velocity
//                reversingMode: xAnimation.reversingMode
//                maximumEasingTime: xAnimation.maximumEasingTime
//            }
//        }

//        property int minX: 0 + wallsThickness
//        property int maxX: rootWindow.width - wallsThickness

//        property int minY: 0 + wallsThickness
//        property int maxY: rootWindow.height - wallsThickness

//        function moveLeft() {
//            movingLeft = true;
//            movingRight = false;
//            x = minX
//        }

//        function moveRight() {
//            movingLeft = false;
//            movingRight = true;
//            x = maxX
//        }

//        function moveUp(dy) {
//            movingUp = true;
//            movingDown = false;
//            y = minY;
//        }

//        function moveDown(dy) {
//            movingUp = false;
//            movingDown = true;
//            y = maxY;
//        }

//        function stopHorizontalMovement() {
//            x = x;
//        }

//        function stopVerticalMovement() {
//            y = y;
//        }

//        Keys.onRightPressed: {
//            moveRight()
//        }

//        Keys.onLeftPressed: {
//            moveLeft()
//        }

//        Keys.onUpPressed: {
//            moveUp()
//        }

//        Keys.onDownPressed: {
//            moveDown()
//        }

//        Keys.onReleased: {
//            if (event.isAutoRepeat)
//                return ;
//            if(event.key == Qt.Key_Left){
//                if (!movingRight) {
//                    stopHorizontalMovement();
//                }
//            }
//            if(event.key == Qt.Key_Right){
//                if (!movingLeft) {
//                    stopHorizontalMovement();
//                }
//            }
//            if(event.key == Qt.Key_Up){
//                if (!movingDown) {
//                    stopVerticalMovement();
//                }
//            }
//            if(event.key == Qt.Key_Down){
//                if (!movingUp) {
//                    stopVerticalMovement();
//                }
//            }
//        }
//    }
}
