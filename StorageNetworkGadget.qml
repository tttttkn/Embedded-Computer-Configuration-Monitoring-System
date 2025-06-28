import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import QtQuick.Shapes 1.12
import QtGraphicalEffects 1.0  // Hoặc phiên bản thấp hơn tùy Qt version
import QtQuick.Controls.Styles 1.4

Button {
//    id: hddnetButton
    y: 121
    width: 115
    height: 117
    background: Rectangle {
        radius: 10
        border.width: 1
        color: parent.down ? buttonPressedColor : "transparent"
    }
    anchors.left: ramButton.right
    anchors.leftMargin: 2
    
    Text {
        id: hddText
        width: wrapMode
        height: wrapMode
        color: "black"
        x: 5
        text: qsTr("HDD")
        font.family: "Times New Roman"
        font.bold: true
        font.pixelSize: 16
        anchors.verticalCenter: parent.top
        anchors.verticalCenterOffset: parent.height * (1/10)
        
    }
    
    
    ProgressBar {
        id: control
        x: 35
        y: 38
        width: 87  // Rộng hơn để đẹp hơn
        height: 8
        anchors.horizontalCenter: parent.horizontalCenter    // Chiều cao mỏng, hiện đại
        value: 1   // Giá trị tiến trình
        
        
        
        background: Rectangle {
            implicitWidth: 200
            implicitHeight: 8
            color: "#555a61"
            radius: height/2        // Bo tròn hoàn toàn
            border.color: "black" // Viền nhẹ
            border.width: 1
            
            
        }
        
        contentItem: Item {
            implicitWidth: 200
            implicitHeight: 8
            
            Rectangle {
                width: control.visualPosition * parent.width
                height: parent.height
                radius: height/2
                border.width: 1
                gradient: Gradient {
                    GradientStop {
                        position: 0
                        color: "#31f8b6"
                    }
                    
                    GradientStop {
                        position: 1
                        color: "#0076ca"
                    }
                }
                // Bo tròn tương tự background
                
                // Gradient màu
                
                
            }
        }
    }
    
    Text {
        id: netText
        width: wrapMode
        height: wrapMode
        color: "black"
        x: 5
        text: qsTr("NETWORK")
        font.family: "Times New Roman"
        font.bold: true
        font.pixelSize: 16
        anchors.verticalCenter: parent.top
        anchors.verticalCenterOffset: parent.height * (6/10)
        
    }
    
    Text {
        id: hddUsage
        y: 50
        text: Math.round(control.value * 100) + "%"
        anchors.left: control.left
        anchors.leftMargin: 0
        font.pixelSize: 12
    }
    
    Text {
        id: element1
        x: 81
        y: 50
        text: qsTr("40°C")
        anchors.right: control.right
        anchors.rightMargin: 0
        font.pixelSize: 12
    }
    
    Image {
        id: image
        y: 89
        width: 30
        height: 20
        anchors.left: parent.left
        anchors.leftMargin: 5
        fillMode: Image.PreserveAspectFit
        source: "qrc:/icon/arrow_upward_24dp.svg"
        
        Text {
            id: element2
            x: 24
            y: 3
            text: qsTr("80.0")
            font.pixelSize: 12
        }
    }
    
    Image {
        id: image1
        x: 55
        y: 89
        width: 30
        height: 20
        anchors.right: parent.right
        anchors.rightMargin: 30
        fillMode: Image.PreserveAspectFit
        source: "/icon/arrow_downward_24dp.svg"
        
        Text {
            id: element3
            x: 23
            y: 3
            text: qsTr("80.0")
            font.pixelSize: 12
        }
    }
}
