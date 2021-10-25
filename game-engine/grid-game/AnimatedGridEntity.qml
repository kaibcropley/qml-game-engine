import QtQuick 2.0

GridBasedEntity {
    id: animatedGridEntity

    property alias spriteSource: sprite.source
    property alias spriteFrameX: sprite.frameX
    property alias spriteFrameY: sprite.frameY
    property alias spriteFrameWidth: sprite.frameWidth
    property alias spriteFrameHeight: sprite.frameHeight
    property alias spriteFrameCount: sprite.frameCount
    property alias spriteFrameDuration: sprite.frameDuration
    property alias spriteInterpolate: sprite.interpolate

    AnimatedSprite {
        id: sprite
        anchors.fill: parent
        interpolate: false
    }
}
