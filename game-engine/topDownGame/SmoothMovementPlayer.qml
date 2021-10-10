import QtQuick 2.5
import "qrc:/"

SmoothMovementEntity {
    id: player

    Controller {
        focus: true
        onMoveLeft: {
            movingLeft = true;
            movingRight = false;
        }

        onMoveRight: {
            movingLeft = false;
            movingRight = true;
        }

        onMoveUp: {
            movingUp = true;
            movingDown = false;
        }

        onMoveDown: {
            movingUp = false;
            movingDown = true;
        }

        onStopMovingLeft: {
            movingLeft = false
        }

        onStopMovingRight: {
            movingRight = false
        }

        onStopMovingUp: {
            movingUp = false
        }

        onStopMovingDown: {
            movingDown = false
        }
    }
}
