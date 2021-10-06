
function shapesCollide(shapeA, shapeB) {
    if (shapeA.colliderRectangle) {
        return rectangleWillCollide(shapeA.getTopLeftCoordinate(), shapeA.getBotRightCoordinate(), shapeB);
    } else {
        return circleWillCollide(shapeA.getCenterCoordinates(), shapeA.radius, shapeB);
    }
}

function rectanglesCollide(rectAPoint1, rectAPoint2, rectBPoint1, rectBPoint2) {
    return (rectAPoint1.x < rectBPoint2.x &&
            rectBPoint1.x < rectAPoint2.x &&
            rectAPoint1.y < rectBPoint2.y &&
            rectBPoint1.y < rectAPoint2.y);
}


function circlesCollide(aCenter, aRadius, bPoint, bRadius) {
    return distanceBetweenCircles(aCenter, bPoint) < aRadius + bRadius;
}

function distanceBetweenCircles(aCenter, bPoint) {
    var dx = aCenter.x - bPoint.x;
    var dy = aCenter.y - bPoint.y;
    return Math.sqrt(dx * dx + dy * dy);
}

// From https://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection
// User e.James - https://stackoverflow.com/users/33686/e-james
function circleAndRectangleCollide(cirCenter, cirRadius, rectCenter, rectWidth, rectHeight) {
    var circleDistanceX = Math.abs(cirCenter.x - rectCenter.x);
    var circleDistanceY = Math.abs(cirCenter.y - rectCenter.y);

    if (circleDistanceX > (rectWidth/2 + cirRadius)) { return false; }
    if (circleDistanceY > (rectHeight/2 + cirRadius)) { return false; }

    if (circleDistanceX <= (rectWidth/2)) { return true; }
    if (circleDistanceY <= (rectHeight/2)) { return true; }

    var cornerDistance_sq = (circleDistanceX - rectWidth/2)^2 +
                         (circleDistanceY - rectHeight/2)^2;

    return (cornerDistance_sq <= (cirRadius^2));
}

function circleWillCollide(cirCenter, cirRadius, otherShape) {
    if (otherShape.colliderRectangle) { // Circle && Rect
        return circleAndRectangleCollide(cirCenter, cirRadius, otherShape.getCenterCoordinates(), otherShape.width, otherShape.height);
    } else { // Circle && Circle
        return circlesCollide(cirCenter, cirRadius, otherShape.getCenterCoordinates(), otherShape.radius);
    }
}

function rectangleWillCollide(rectPoint1, rectPoint2, otherShape) {
    if (otherShape.colliderRectangle) { // Rect && Rect
        return rectanglesCollide(rectPoint1, rectPoint2, otherShape.getTopLeftCoordinates(), otherShape.getBotRightCoordinates());
    } else { // Rect && Circle
        return circleAndRectangleCollide(otherShape.getCenterCoordinates(), otherShape.radius, getRectangleCenterCoordinates(rectPoint1, rectPoint2), Math.abs(rectPoint1.x - rectPoint2.x), Math.abs(rectPoint1.y - rectPoint1.y));
    }
}

function getRectangleCenterCoordinates(rectPoint1, rectPoint2) {
    return Qt.point((rectPoint1.x + rectPoint2.x) / 2, (rectPoint1.y + rectPoint1.y) / 2);
}
