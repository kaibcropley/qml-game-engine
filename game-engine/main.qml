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
    title: qsTr("Hello World")

    property bool collisionsRunning: true

    Component.onCompleted: {
        gameBoard.createRandomizedGameBoard(gameGrid.columns, gameGrid.rows);
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            entityManager.findPath(Qt.point((mouseX / 100) - 1, (mouseY / 100) - 1));
            movementTimer.restart();
        }
    }

    GameGrid {
        id: gameGrid
        columns: 10
        rows: 10
        anchors {
            fill: parent
        }

        Component.onCompleted: {
            model = gameBoard.gameBoardToOneDimension();
        }
    }

    GridBasedEntity {
        id: entity
        width: 50
        height: 50
        color: "blue"

        x: (gridEntity.gridPos.x * 100) + 25
        y: (gridEntity.gridPos.y * 100) + 25

        onGridXChanged: {
            console.log("Grid X changed");
        }

        Component.onCompleted: {
            entityManager.registerEntity(gridEntity);
            entityManager.findPath(Qt.point(8, 6));
            movementTimer.start();
        }
        focus: true

        Keys.onSpacePressed: {
            gridEntity.followPath(1);
        }
    }

    Timer {
        id: movementTimer
        repeat: true
        interval: 500
        triggeredOnStart: true

        onTriggered: {
            entity.gridEntity.followPath(1);
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
