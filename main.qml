import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import QtQuick.Shapes 1.12
import QtGraphicalEffects 1.0  // Hoặc phiên bản thấp hơn tùy Qt version
import QtQuick.Controls.Styles 1.4

Window {
    id: window
    visible: true
    width: 320
    height: 240
    maximumHeight: height
    maximumWidth: width

    minimumHeight: height
    minimumWidth: width
    color: "#cacaca"

    title: "System Dashboard"
   //     flags: Qt.Window | Qt.FramelessWindowHint

    property color buttonColor: "#3498db"
    property color buttonPressedColor: "#2980b9"
    property color menuColor: "#2c3e50"
    property color menuPressedColor: "#34495e"

    MenuBarView {}
//        id: menuBar


    StackView {
        id: stackView
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 34
        anchors.right: parent.right
        anchors.rightMargin: 0
        //        initialItem: Qt.resolvedUrl("HomeGadget.qml")
        initialItem: HomeGadget {}
//        initialItem: Qt.resolvedUrl("CpuPage.qml")



    }
}







