import QtQuick 2.0
import "qrc:/"
import "qrc:/grid-game/"

Item {
    id: bugGame

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
        running: true

        onTriggered: {
            var entities = [ entity, entity2 ];

            for (var i = 0; i < entities.length; i++)  {
                var currEntity = entities[i];
                if (currEntity.pathHasSteps()) {
                    currEntity.followPath(1);
                } else {
                    var p = bugGame.findNearestFood(currEntity);
                    if (p !== undefined && p !== null) {
                        currEntity.findPath(p);
                        findNearestBug(currEntity, entities);
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

    // Returns nearest bug entity or undefined
    function findNearestBug(targetEntity, entities) {
        var source = targetEntity.gridPos;
        var currTargetBug = undefined;
        var currTargetBugDistance = gameGrid.rows * gameGrid.columns;

        for (var i = 0; i < entities.length; i++)  {
            var currEntity = entities[i];
            if (currEntity !== targetEntity && !currEntity.dying &&  targetEntity.bugType > currEntity.bugType) {
                var distance = distanceBetween(source, currEntity.gridPos);
                if (distance < currTargetBugDistance) {
                    currTargetBug = currEntity;
                    currTargetBugDistance = distance;
                }
            }
        }
        return currTargetBug;
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

        delegate: BugGridSquare {
            id: square
            width: 100
            height: 100

            backgroundSource: "/demos/bugs/images/dirt.png"
            gridPos:  modelData.gridPos.toString()
            movementAllowed: modelData.movementAllowed
            containsFood: modelData.containsFood
        }
    }

    BugEntity {
        id: entity
        width: 50
        height: 50

        bugType: 8
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

        bugType: 5
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

    BugEntity {
        id: playerBug
        width: 50
        height: 50

        bugType: 12
        maxDuration: movementTimer.interval
        rotation: lastDirection;

        gridPos: Qt.point(8, 3)

        onMovementStopped: {
            var targetEntity = playerBug;
            var entities = [ entity, entity2 ];
            for (var i = 0; i < entities.length; i++)  {
                var currEntity = entities[i];
                if (currEntity !== targetEntity && !currEntity.dying &&  targetEntity.bugType > currEntity.bugType) {
                    if (currEntity.gridPos === targetEntity.gridPos) {
                        currEntity.movementEnabled = false;
                        currEntity.dying = true;
                    }
                }
            }
        }

        Controller {
            focus: true
            disableAutoRepeat: true

            function move(dx, dy) {
                var currPoint = Qt.point(playerBug.gridPos.x + dx, playerBug.gridPos.y + dy);

                if (currPoint.x < 0 || currPoint.y < 0) {
                    return;
                }

                if (gameGrid.getSquare(currPoint).movementAllowed) {
                    playerBug.gridPos = currPoint;
                }
            }

            onMoveLeft: {
                move(-1,0);
            }

            onMoveRight: {
                move(1,0);
            }

            onMoveUp: {
                move(0,-1);
            }

            onMoveDown: {
                move(0,1);
            }
        }
    }
}
