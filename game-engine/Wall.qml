import QtQuick 2.0

RectangleCollider {
    id: wall
    height: thickness
    width: thickness
    color: "lightgrey"
    border.width: 0

    property int thickness: 30
}
