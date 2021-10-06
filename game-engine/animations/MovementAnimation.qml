import QtQuick 2.0

SmoothedAnimation {
    id: movementAnimation

    property bool movePositive: true
    property bool moveX: true
    property int movementSpeed

    property int targetProperty: moveX ? target.x : target.y

    function startAnimation(movePositive) {
//        movementAnimation.stop();
        movementAnimation.movePositive = movePositive;
        movementAnimation.restart();

        if (!movementAnimation.running) {
            movementAnimation.start();
        }
    }

//    velocity: 200

    loops: Animation.Infinite
    property: moveX ? "x" : "y"
    from: targetProperty
    to: (movePositive ? targetProperty + movementSpeed : targetProperty - movementSpeed)
}
