import QtQuick 2.0

Rectangle {
    id: hand
    color: "darkblue"
    height: 500
    anchors {
        verticalCenter: parent.verticalCenter
        left: parent.left
        right: parent.right
    }

    Row {
        id: cardBoundingBox
        anchors {
            centerIn: parent
        }
        spacing: 4

        Repeater {
            id: cardRepeater
            model: 15

            delegate: Card {
                width: 40
                height: 75

                rotation: pickedUp ? 0 : Math.ceil(cardRepeater.count / 2) == index + 1 ? 0 : (Math.floor(cardRepeater.count / 2) - (index)) * -12
                Component.onCompleted: {
                    y += Math.abs((Math.floor(cardRepeater.count / 2) - (index)) * 3);
                }

                onPickedUpChanged: {
                    if (!pickedUp) {
                        console.log("Dropped at ", x, ",", y);
                    }
                }
            }
        }
    }
}
