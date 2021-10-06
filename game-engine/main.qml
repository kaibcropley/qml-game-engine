import QtQuick 2.6
import QtQuick.Window 2.2
import "qrc:/animations/"
import "qrc:/topDownGame/"
import "qrc:/cardGame/"
import "qrc:/CollisionManager.js" as CollisionManager

Window {
    id: rootWindow
    visible: true
    width: 1000
    height: 1000
    title: qsTr("Hello World")

    property bool collisionsRunning: true

    BorderWalls {
        anchors.fill: parent
    }



    function getRandomInt(min, max) {
        min = Math.ceil(min);
        max = Math.floor(max);
        return Math.floor(Math.random() * (max - min + 1)) + min;
    }
}
