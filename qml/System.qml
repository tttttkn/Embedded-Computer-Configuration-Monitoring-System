import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import QtQuick.Shapes 1.12
import QtGraphicalEffects 1.0

Rectangle {
    anchors.fill: parent
    color: "transparent"
    border.color: "black"
    radius: 5

    ColumnLayout {
        anchors.fill: parent
        spacing: 2
        anchors.leftMargin: 3  // Thêm lề trái chung cho cả ColumnLayout

        Text {
            text: "Host name: " + modelController.staticSystemInfo.hostname
            font.pixelSize: 15
            Layout.leftMargin: 3  // Sử dụng Layout.leftMargin thay vì anchors.leftMargin
        }

        Text {
            text: "OS version: " + modelController.staticSystemInfo.os
            font.pixelSize: 15
            Layout.leftMargin: 3
        }

        Text {
            text: "Kernel version: " + modelController.staticSystemInfo.kernelVersion
            font.pixelSize: 15
            Layout.leftMargin: 3
        }

        Text {
            text: "Uptime: " + modelController.uptime
            font.pixelSize: 15
            Layout.leftMargin: 3
        }

        Timer {
            id: clockTimer1
            interval: 1000  
            running: true
            repeat: true
            onTriggered: {
                var now = new Date()
                sysTime.text = "System Time: " + Qt.formatTime(now, "hh:mm:ss")
            }
        }
        
        Text {
            id: sysTime
            font.pixelSize: 15
            Layout.leftMargin: 3
        }
    }
}