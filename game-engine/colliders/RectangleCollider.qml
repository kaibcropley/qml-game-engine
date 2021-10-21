import QtQuick 2.0

Rectangle {
    id: rectCollider

    color: "transparent"

    property bool colliderRectangle: true

    function getAsQRect() {
        return Qt.rect(rectCollider.x, rectCollider.y, rectCollider.width, rectCollider.height);
    }

    function getCenterCoordinates() {
        return Qt.point(x + (width / 2), y + (height / 2));
    }

    property int centerX: x + (width / 2)
    property int centerY: y + (height / 2)

    function getTopLeftCoordinates() {
        return Qt.point(x, y);
    }

    function getBotRightCoordinates() {
        return Qt.point(x + width, y + height);
    }


    function isTouchingRect(other) {
        var topLeft = getTopLeftCoordinates();
        var botRight = getBotRightCoordinates();
        var otherTopLeft = other.getTopLeftCoordinates();
        var otherBotRight = other.getBotRightCoordinates();

        return (topLeft.x < otherBotRight.x &&
                otherTopLeft.x < botRight.x &&
                topLeft.y < otherBotRight.y &&
                otherTopLeft.y < botRight.y)
    }
}
