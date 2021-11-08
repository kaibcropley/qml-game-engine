import QtQuick 2.0
import "qrc:/grid-game/"

BugEntity {
    id: carnivoreBug

    function takeAction() {
        setObjective();
        if (pathHasSteps()) {
            followPath(1);
        }
    }

    function setObjective() {
        var bug = findNearestBug(carnivoreBug, bugGame.entities);
        if (bug !== undefined) {
            findPath(bug.gridPos);
        }
    }

    // Returns nearest bug entity or undefined
    function findNearestBug(targetEntity, entities) {
        var source = targetEntity.gridPos;
        var currTargetBug = undefined;
        var currTargetBugDistance = gameGrid.rows * gameGrid.columns;

        for (var i = 0; i < entities.length; i++)  {
            var currEntity = entities[i];
            if (currEntity !== targetEntity && !currEntity.dying ) { //&&  targetEntity.bugType > currEntity.bugType) {
                var distance = bugGame.distanceBetween(source, currEntity.gridPos);
                if (distance < currTargetBugDistance) {
                    currTargetBug = currEntity;
                    currTargetBugDistance = distance;
                }
            }
        }
        return currTargetBug;
    }

    function collisionCheck() {
        var bug = entityManager.checkForEntityCollision(carnivoreBug);
        if (bug !== undefined && bug !== null && bug !== 0) {
            try {
                bug.alive = false;
            } catch (error) {
                console.log("carnivoreBug.onMovementStopped: ", error);
            }
        }
    }

    onMovementStarted: {
        collisionCheck();
    }

    onMovementStopped: {
        collisionCheck();
    }
}
