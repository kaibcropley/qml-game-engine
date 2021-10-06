import QtQuick 2.0

// BorderWalls is a simple call to make a surrounding box of walls around the screen
Item {
    anchors.fill: parent

    property int wallsThickness: 30

    Wall {
        id: leftWall
        height: parent.height
        thickness: wallsThickness

        x: 0
        y: 0
    }

    Wall {
        id: rightWall
        height: parent.height
        thickness: wallsThickness

        x: parent.width - width
        y: 0
    }

    Wall {
        id: topWall
        width: parent.width
        thickness: wallsThickness

        x: 0
        y: 0
    }

    Wall {
        id: botWall
        width: parent.width
        thickness: wallsThickness

        x: 0
        y: parent.height - height
    }
}
