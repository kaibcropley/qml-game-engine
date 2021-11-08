import QtQuick 2.0
import "qrc:/grid-game/"

BugEntity {
    id: ai

    property int recheckObjectiveMax: 3
    property int recheckObjectiveCurrent: 0

    function takeAction() {
        if (ai.pathHasSteps() && gameGrid.getSquare(ai.getPathNextStep()).movementAllowed) {
            if (recheckObjectiveCurrent <= 0 || !gameGrid.getSquare(ai.getPathTarget()).containsFood) {
                setObjective(); // Set objective resets recheckObjectiveCurrent
            }
            ai.followPath(1);
            recheckObjectiveCurrent++;

        } else {
            setObjective();
            takeAction();
        }
    }

    function setObjective() {
        recheckObjectiveCurrent = 0;

        var p = bugGame.findNearestValidSquare(ai, function(square){
            return square.containsFood
        });

        if (p !== undefined) {
            if (findPath(p)) {
                return;
            }
        }

        // No Objective Found (or no path to objective found)
        //  Go to random location
//        p =


    }

    onMovementStopped: {
        var currSquare = gameGrid.getSquare(gridPos);
        if (currSquare.containsFood) {
            currSquare.containsFood = false;
        }
    }
}
