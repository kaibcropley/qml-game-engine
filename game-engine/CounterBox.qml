import QtQuick 2.0

//Rectangle {
//    width: 50
//    height: width
//    color: "red"

//    anchors {
//        top: counterBox.bottom; topMargin: 15
//        horizontalCenter: counterBox.horizontalCenter
//    }

//    MouseArea {
//        anchors.fill: parent

//        onClicked: {
//            if (counterBox.highlightIndex < counterBox.maxCounters) {
//                counterBox.highlightIndex += getRandomInt(0, 6);
//            } else {
//                counterBox.highlightIndex = 0;
//            }
//        }
//    }
//}

Rectangle {
    id: counterOuterBox
    height: 500
    width: 500

    border {
        width: 5
        color: counterBackground
    }

    property alias background: counterOuterBox.color
    property color counterBackground: "darkgrey"
    property color counterHighlightBackground: "yellow"

    property alias maxCounters: counterRepeater.model
    property int highlightIndex

    Row {
        id: counterRow
        anchors {
            fill: parent
            margins: 15
        }
        spacing: 5

        Repeater {
            id: counterRepeater
            delegate: Rectangle {
                color: index + 1 <= counterOuterBox.highlightIndex ? counterHighlightBackground : counterBackground
                anchors {
                    top: parent.top;
                    bottom: parent.bottom
                }
                width: (counterRow.width - counterRow.spacing * (counterRepeater.count - 1)) / (counterRepeater.count)
            }
        }
    }
}
