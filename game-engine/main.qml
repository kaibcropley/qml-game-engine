import QtQuick 2.6
import QtQuick.Window 2.2
import "qrc:/colliders/"
import "qrc:/gridGame/"
import "qrc:/gridGame/bugEntities/"
import kcropley.grid 1.0
import movement.enums 1.0
//import "qrc:/cardGame/"
//import "qrc:/CollisionManager.js" as CollisionManager

Window {
    id: rootWindow
    visible: true
    width: 1000
    height: 1000
    title: qsTr("Game Engine")

    property bool collisionsRunning: true

    Component.onCompleted: {
        gameBoard.createRandomizedGameBoard(gameGrid.columns, gameGrid.rows);
    }

    GameGrid {
        id: gameGrid
        columns: 10
        rows: 10
        anchors {
            fill: parent
        }

        Component.onCompleted: {
            model = gameBoard.gameBoardToOneDimension();
        }
    }

    BugEntity {
        id: entity
        width: 50
        height: 50

        x: (gridX * 100) + 25
        y: (gridY * 100) + 25

        bugType: 6

        rotation: MovementEnums.NW

        Component.onCompleted: {
            entityManager.registerEntity(entity);
        }
    }

    BugEntity {
        id: entity2
        width: 50
        height: 50

        x: (2 * 100) + 25
        y: (2 * 100) + 25

        bugType: 2

        Component.onCompleted: {
            entityManager.registerEntity(entity);
        }
    }
}
