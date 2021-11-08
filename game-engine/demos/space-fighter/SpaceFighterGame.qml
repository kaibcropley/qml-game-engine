import QtQuick 2.0
import "qrc:/physics-game/colliders/"

Item {

    Component.onCompleted: {
        gameTimer.start();
    }

    MouseArea {
        anchors.fill: parent

        onMouseXChanged: {
            moveableEntity.x = mouseX;
        }

        onMouseYChanged: {
            moveableEntity.y = mouseY;
        }
    }

    Timer {
        id: gameTimer
        interval: 500
        repeat: true

        onTriggered: {
            if (collisionManager.collision(moveableEntity, other)) {
                console.log("Collision!");
            }
        }
    }

    CircleEntity {
        id: moveableEntity
        width: 50
        height: 50


        Image {
            source: "./images/Spaceship-shooter-environment/Spaceship-shooter-environment/spritesheets/ship.png"
//            x: width * 3
            width: 16
            height: 24
//            sourceSize.width: width * 5
//            sourceSize.height: height * 2
            fillMode: Image.PreserveAspectCrop
            clip: true

        }
    }

    CircleEntity {
        id: other
        width: 50
        height: 50
        x: 100
        y: 125

        Rectangle {
            id: collision
            anchors.fill: parent
            radius: width / 2
            color: "lightblue"
        }
    }

}
