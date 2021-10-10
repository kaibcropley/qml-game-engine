import QtQuick 2.5
import "qrc:/"

GridBasedEntity {
    id: gridPlayer

    Controller {
        focus: true

        onMoveLeft: {
            gridPlayer.moveLeft();
        }

        onMoveRight: {
            gridPlayer.moveRight();
        }

        onMoveUp: {
            gridPlayer.moveUp();
        }

        onMoveDown: {
            gridPlayer.moveDown();
        }
    }
}
