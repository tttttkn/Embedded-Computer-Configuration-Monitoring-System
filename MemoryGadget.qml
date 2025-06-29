import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import QtQuick.Shapes 1.12
import QtGraphicalEffects 1.0  // Hoặc phiên bản thấp hơn tùy Qt version

Button {
//    id: ramButton
    width: 100
    anchors.left: parent.left
    anchors.leftMargin: 2
    anchors.topMargin: 2
    anchors.bottomMargin: 2
    height: (parent.height - spacing) / 2
    anchors.bottom: parent.bottom
    background: Rectangle {
        color: parent.down ? buttonPressedColor : "transparent"
        border.color: "black"
        radius: 10
    }
    
    Text {
        id: ramText
        width: wrapMode
        height: wrapMode
        color: "black"
        x: 5
        text: qsTr("RAM")
        font.family: "Times New Roman"
        font.bold: true
        font.pixelSize: 16
        styleColor: "#cf4e4e"
        anchors.verticalCenter: parent.top
        anchors.verticalCenterOffset: parent.height * (1/10)
        
    }
    
    ProgressCircle {
        id: progress1
        lineWidth: 10
        value: memoryModel.memoryInfo.ramUsage / 100
        size: 80
        secondaryColor: "#585252"
        primaryColor: "#0787c1"
        
        ColorAnimation {
            from: "white"
            to: "red"
            duration: 200
        }
        anchors.verticalCenter: parent.top
        anchors.verticalCenterOffset: parent.height * (3/5)
        anchors.horizontalCenter: parent.left
        anchors.horizontalCenterOffset: parent.width / 2
        
        Text {
            text: parseInt(progress1.value * 100) + "%"
            anchors.centerIn: parent
            font.pointSize: 10
//            color: progress1.primaryColor
            color: "black"

        }
    }
    
}
