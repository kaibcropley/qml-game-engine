import QtQuick 2.0

Item {
    id: controller

    // Movement beginners
    signal moveLeft()
    signal moveRight()
    signal moveUp()
    signal moveDown()

    // Movement stoppers
    signal stopMovingLeft()
    signal stopMovingRight()
    signal stopMovingUp()
    signal stopMovingDown()

    property bool disableAutoRepeat: false

    Keys.onLeftPressed: {
        if (disableAutoRepeat && event.isAutoRepeat)
            return;
        moveLeft();
    }

    Keys.onRightPressed: {
        if (disableAutoRepeat && event.isAutoRepeat)
            return;
        moveRight();
    }

    Keys.onUpPressed: {
        if (disableAutoRepeat && event.isAutoRepeat)
            return;
        moveUp();
    }

    Keys.onDownPressed: {
        if (disableAutoRepeat && event.isAutoRepeat)
            return;
        moveDown();
    }

    Keys.onReleased: {
        if (disableAutoRepeat && event.isAutoRepeat)
            return;
        if(event.key == Qt.Key_Left){
            stopMovingLeft();
        }
        if(event.key == Qt.Key_Right){
            stopMovingRight();
        }
        if(event.key == Qt.Key_Up){
            stopMovingUp();
        }
        if(event.key == Qt.Key_Down){
            stopMovingDown();
        }
    }
}
