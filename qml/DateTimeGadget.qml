import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import QtQuick.Shapes 1.12
import QtGraphicalEffects 1.0  // Hoặc phiên bản thấp hơn tùy Qt version
import QtQuick.Controls.Styles 1.4


Button {
//    id: datetime
    y: 121
    height: 117
    background: Rectangle {
        color: parent.down ? buttonPressedColor : "transparent"
        radius: 10
        border.width: 1
    }
    
    anchors.right: parent.right
    anchors.rightMargin: 2
    anchors.left: hddnetButton.right
    anchors.leftMargin: 2
    
    Text {
        id: dateText
        x: 5
        width: wrapMode
        height: wrapMode
        color: "#000000"
        text: qsTr("DATE")
        anchors.verticalCenterOffset: parent.height * (1/10)
        font.bold: true
        font.pixelSize: 16
        anchors.verticalCenter: parent.top
        font.family: "Times New Roman"
    }
    
    Text {
        id: timeText
        x: 5
        width: wrapMode
        height: wrapMode
        color: "#000000"
        text: qsTr("TIME")
        anchors.verticalCenterOffset: parent.height * (5.5/10)
        font.bold: true
        font.pixelSize: 16
        anchors.verticalCenter: parent.top
        font.family: "Times New Roman"
    }
    
    Timer {
        id: clockTimer
        interval: 1000  // cập nhật mỗi giây
        running: true
        repeat: true
        onTriggered: {
            var now = new Date()
            element4.text = Qt.formatDate(now, "dd/MM/yyyy")
            element5.text = Qt.formatTime(now, "hh:mm:ss")
        }
    }
    Text {
        id: element4
        x: 25
        y: 38
        anchors.right: parent.right
        anchors.rightMargin: 10
        font.pixelSize: 12
    }
    
    Text {
        id: element5
        x: 58
        y: 85
        anchors.right: parent.right
        anchors.rightMargin: 10
        font.pixelSize: 13
    }
}



