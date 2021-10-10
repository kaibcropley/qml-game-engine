import QtQuick 2.0
import "qrc:/topDownGame/"

SmoothMovementPlayer {
    id: entity
    width: 90
    height: width
    color: "lightgreen"
    focus: true

    x: 500
    y: 500

    possibleMovementCollisions: [topWall, botWall, rightWall, leftWall]

    property int jumpHeight: 400
    property int minY: 500

    property alias jumpSpeed: jumpUpAnimation.velocity
    property alias fallSpeed: fallDownAnimation.velocity

    Keys.onSpacePressed: {
        jumpAnimation.restart();
    }

    SequentialAnimation {
        id: jumpAnimation
        SmoothedAnimation {
            id: jumpUpAnimation
            target: entity
            property: "y"
            easing.type: Easing.OutQuart
            to: entity.y - entity.jumpHeight
        }

        SmoothedAnimation {
            id: fallDownAnimation
            target: entity
            property: "y"
            easing.type: Easing.InOutQuart
            to: entity.minY
        }
    }
}
