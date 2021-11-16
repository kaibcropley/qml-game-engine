import QtQuick 2.0
import "qrc:/physics-game/colliders/"

CircleEntity {
    id: moveableEntity

    property alias imageSource: image.source

    Image {
        id: image
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
    }
}
