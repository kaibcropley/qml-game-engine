import QtQuick 2.0
import kcropley.grid 1.0
import "qrc:/"
import "qrc:/grid-game/"

Item {
    id: bugGame

    property var entities: [ ]

    property alias rows: gameGrid.rows
    property alias columns: gameGrid.columns

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton

        onClicked: {
            var p = Qt.point(Math.ceil(mouseX / (bugGame.width / gameGrid.rows)) - 1, Math.ceil(mouseY / (bugGame.height / gameGrid.columns)) - 1);

            if (mouse.button === Qt.RightButton) { // 'mouse' is a MouseEvent argument passed into the onClicked signal handler
                gameGrid.getSquare(p).movementAllowed = false;
                if (gameGrid.getSquare(p).containsFood) {
                    gameGrid.getSquare(p).containsFood = false;
                }
            } else if (mouse.button === Qt.LeftButton) {
                makeBug(p, getRandomInt(0, 12));
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
            for (var i = 0; i < entities.length; i++)  {
                if (entities[i].alive) {
                    entities[i].takeAction();
                } else {
                    entities[i].timeDead += 1;
                    if (entities[i].timeDead >= 3) { // Give a delay to the death of the entity
                        entities[i].destroy();
                        var copy = entities;
                        copy.splice(i, 1);
                        entities = copy;
                    }
                }
            }
        }
    }

    function getRandomInt(min, max) {
      min = Math.ceil(min);
      max = Math.floor(max);
      return Math.floor(Math.random() * (max - min) + min); //The maximum is exclusive and the minimum is inclusive
    }

    function findNearestWater(targetEntity) {
        return findNearestValidSquare(targetEntity, function(square){
            return square.containsWater
        });
    }

    // Returns QPoint or undefined
    // squareValidityCheck is expected to be formatted like: bool squareValidityCheck(GridSquare)
    function findNearestValidSquare(targetEntity, squareValidityCheck) {
        var source = targetEntity.gridPos;
        var currTargetFood;
        var currTargetFoodDistance = gameGrid.rows * gameGrid.columns;

        for (var row = 0; row < gameGrid.rows; row++) {
            for (var col = 0; col < gameGrid.columns; col++) {
                var currPoint = Qt.point(row, col);
                if (squareValidityCheck(gameGrid.getSquare(currPoint))) {
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
        if (p1 === undefined || p2 === undefined) {
            console.log("Error: distanceBetween", p1, p2);
            return 9999;
        }

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
//            model = gridMatrix.matrixToOneDimension();
            var tempModel = [];
            for (var row = 0; row < rows; row++) {
                for (var col = 0; col < columns; col++) {
                    var movementAllowed = getRandomInt(0, 5) !== 1;
                    var containsFood = movementAllowed ? getRandomInt(0, 10) === 1 : false;
                    tempModel.push(createGridSquare(Qt.point(col, row), movementAllowed, containsFood));
                }
            }
            model = tempModel;
        }

        function createGridSquare(p, allowMovement, containFood) {
            return  {
                gridPos: p,
                movementAllowed: allowMovement,
                containsFood: containFood
            }
        }

        delegate: BugGridSquare {
            id: square
            width: gameGrid.width / gameGrid.columns
            height: gameGrid.height / gameGrid.rows

            backgroundSource: "/demos/bugs/images/dirt.png"
            gridPos:  modelData.gridPos
            movementAllowed: modelData.movementAllowed
            containsFood: modelData.containsFood
        }
    }

    function makeBug(gridPos, bugType) {
        var component = Qt.createComponent("VegetarianBug.qml");
        var bug = component.createObject(bugGame, {
                                             "maxDuration": movementTimer.interval,
                                             "gridPos": gridPos,
                                             "bugType": bugType
                                         });

        var copy = entities;
        copy.push(bug);
        entities = copy;

        if (bug === null) {
            // Error Handling
            console.log("Error creating bug");
        }
    }

    CarnivoreBug {
        id: carnivoreBug
        width: 50
        height: 50

        bugType: 12
        maxDuration: movementTimer.interval
        rotation: lastDirection;

        gridPos: Qt.point(8, 3)

        Timer {
            id: carnivoreBugMovementTimer
            interval: 500
            triggeredOnStart: true
            repeat: true
            running: true

            onTriggered: {
                carnivoreBug.takeAction();
            }
        }
    }

    TileSet {
        
    }

//    BugEntity {
//        id: playerBug
//        width: 50
//        height: 50

//        bugType: 12
//        maxDuration: movementTimer.interval
//        rotation: lastDirection;

//        gridPos: Qt.point(8, 3)

//        onMovementStopped: {
//            var targetEntity = playerBug;
//            for (var i = 0; i < entities.length; i++)  {
//                var currEntity = entities[i];
//                if (currEntity !== targetEntity && !currEntity.dying &&  targetEntity.bugType > currEntity.bugType) {
//                    if (currEntity.gridPos === targetEntity.gridPos) {
//                        currEntity.movementEnabled = false;
//                        currEntity.dying = true;
//                    }
//                }
//            }
//        }

//        Controller {
//            focus: true
//            disableAutoRepeat: true

//            function move(dx, dy) {
//                var currPoint = Qt.point(playerBug.gridPos.x + dx, playerBug.gridPos.y + dy);

//                if (currPoint.x < 0 || currPoint.y < 0) {
//                    return;
//                }

//                if (gameGrid.getSquare(currPoint).movementAllowed) {
//                    playerBug.gridPos = currPoint;
//                }
//            }

//            onMoveLeft: {
//                move(-1,0);
//            }

//            onMoveRight: {
//                move(1,0);
//            }

//            onMoveUp: {
//                move(0,-1);
//            }

//            onMoveDown: {
//                move(0,1);
//            }
//        }
//    }

}
