import QtQuick 2.6
import QtQuick.Window 2.2
import "qrc:/grid-game/"
import "qrc:/demos/bugs/"
import kcropley.grid 1.0

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
            if (!currSquare.blocked) {
                currSquare.containsFood = true;
            }
        }
    }

    Timer {
        id: movementTimer
        interval: 750 //400
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
        rotation: lastDirection;

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

        rotation: lastDirection;

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
}
