import QtQuick 2.0
import "qrc:/grid-game/"

AnimatedGridEntity {
    id: bug

    property int bugType: 0
    property bool walking:false
    property bool dying: !alive
    property int timeDead: 0

    property bool alive: true

    movementEnabled: alive

    spriteSource: "./images/Little Alchemist Lab BugsSpriteSheet.png"
    spriteFrameWidth: 32
    spriteFrameHeight: 32
    spriteFrameCount:  walking ? 8 : (dying ? 4 : (bugType % 2 === 0 ? 3 : 1))
    spriteFrameDuration: 200
    spriteFrameX: walking ? (spriteFrameWidth * 4) : (dying ? (spriteFrameWidth * 13) : 0)
    spriteFrameY: spriteFrameHeight * bugType

    width: 50
    height: 50

    rotation: lastDirection;

//    function setRandomPath() {
//        var p;
//        while (!pathHasSteps()) {
//            findPath(Qt.point(bugGame.getRandomInt(0, bugGame.rows), bugGame.getRandomInt(0, bugGame.columns)));
//        }
//    }
}
