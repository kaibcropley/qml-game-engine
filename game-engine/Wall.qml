import QtQuick 2.0
import "qrc:/colliders/"

RectangleCollider {
    id: wall
    height: thickness
    width: thickness
    color: "lightgrey"
    border.width: 0

    property int thickness: 30
}
