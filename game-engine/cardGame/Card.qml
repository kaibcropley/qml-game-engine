import QtQuick 2.0

Rectangle {
    id: card
    color: "pink"
    radius: 8

    property int scaleSize: 3
    property alias pickedUp: cardMouseArea.pressed

    MouseArea {
        id: cardMouseArea
        anchors.fill: parent
        drag.target: card
        drag.axis: Drag.XAndYAxis
//        drag.minimumX: 0
//        drag.maximumX: card.parent.width - card.width
//        drag.minimumY: 0
//        drag.maximumY: card.parent.height - card.height

        onPressedChanged: {
            if (pressed) {
                card.scale = card.scaleSize;
            } else {
                card.scale = 1;
            }
        }
    }
}
