import QtQuick 2.0

AnimatedGridEntity {
    id: bug
    width: 50
    height: 50
    color: "transparent"

    spriteSource: "/images/Little Alchemist Lab BugsSpriteSheet.png"
    spriteFrameWidth: 32
    spriteFrameHeight: 30
    spriteFrameCount: 8
    spriteFrameDuration: 200
    spriteFrameX: spriteFrameWidth * 4
}
