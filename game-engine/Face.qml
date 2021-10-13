import QtQuick 2.0

Rectangle {
    id: face

    property color eyeColor: "black"

    border {
        width: 2
        color: "black"
    }

    Rectangle {
        id: leftEye
        color: eyeColor
        width: face.width
        height: width
    }

    Rectangle {
        id: rightEye
        color: eyeColor
        width: face.width
        height: width
    }
}
