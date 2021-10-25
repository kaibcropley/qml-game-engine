import QtQuick 2.6
import QtQuick.Window 2.2
import "qrc:/demos/bugs/"
import kcropley.grid 1.0

Window {
    id: rootWindow
    visible: true
    width: 1000
    height: 1000
    title: qsTr("QML Game Engine")

    BugGame {
        anchors.fill: parent
    }
}
