import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import QtQuick.Shapes 1.12
import QtGraphicalEffects 1.0  // Hoặc phiên bản thấp hơn tùy Qt version

Button {
//    id: cpuButton
    anchors.left: parent.left
    anchors.leftMargin: 2
    anchors.topMargin: 2
    anchors.rightMargin: 2
    anchors.bottomMargin: 2
    width: (parent.width - spacing) / 2
    height: (parent.height - spacing) / 2
    anchors.top: parent.top
    background: Rectangle {
        color: parent.down ? buttonPressedColor : "transparent"
        border.color: "black"
        radius: 10
    }

    
    Text {
        id: cpuText
        width: wrapMode
        height: wrapMode
        color: "black"
        x: 5
        text: qsTr("CPU MOD")
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
        value: cpuModel.cpuUsage / 100

        size: 80
        secondaryColor: "#585252"
        primaryColor: "#0787c1"

//        ColorAnimation {
//            from: "white"
//            to: "red"
//            duration: 200
//        }
        anchors.verticalCenter: parent.top
        anchors.verticalCenterOffset: parent.height * (3/5)
        
        Text {
            text: parseInt(progress1.value * 100) + "%"
            anchors.centerIn: parent
            font.pointSize: 10
//            color: progress1.primaryColor
            color: "black"
        }
    }
    
    
    ProgressBar {
        id: control
        x: 82
        y: 45
        width: 50  
        height: 8       
        value: cpuModel.cpuTemp / 100

        Behavior on value {
            NumberAnimation {
                duration: 500  
                easing.type: Easing.InOutQuad  
            }
        }

        background: Rectangle {
            implicitWidth: 200
            implicitHeight: 8
            color: "#555a61"
            radius: height/2        
            border.color: "black" 
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
                
              }
            }
        }

    
    ProgressBar {
        id: control1
        x: 82
        y: 70
        width: 50  
        height: 8   
        
        Behavior on value {
            NumberAnimation {
                duration: 500  
                easing.type: Easing.InOutQuad  
            }
        }

        value: cpuModel.cpuClock / 1000

        background: Rectangle {
            implicitWidth: 200
            implicitHeight: 8
            color: "#555a61"       // Màu nền sáng hơn
            radius: height/2
            border.width: 1        // Bo tròn hoàn toàn

        }
        
        contentItem: Item {
            x: 0
            implicitWidth: 200
            implicitHeight: 8
            
            Rectangle {
                width: control1.visualPosition * parent.width
                height: parent.height
                color: "#31f8b6"
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

            }
        }
    }
    
    Rectangle {
        id: temp
        x: 78
        y: 54
        
        color: "transparent"
        width: 58
        height: 10
        Text {
            id: tempText
            anchors.left: parent.left
            anchors.top: parent.top
            text: qsTr("TEMP")
            color: "black"
            font.bold: true
            font.family: "Times New Roman"
            font.pixelSize: 8
        }
        
        Text {
            id: tempValue
            anchors.right: parent.right
            anchors.top: parent.top
            text: cpuModel.cpuTemp.toFixed(1) + "°C"
            color: "black"
            font.bold: true
            font.family: "Times New Roman"
            font.pixelSize: 8
        }
        
    }
    
    Rectangle {
        id: clock
        x: 78
        y: 79
        
        color: "transparent"
        width: 58
        height: 10
        Text {
            id: clockText
            anchors.left: parent.left
            anchors.top: parent.top
            text: qsTr("CLK")
            color: "black"
            font.bold: true
            font.family: "Times New Roman"
            font.pixelSize: 8
        }
        
        Text {
            id: clockValue
            anchors.right: parent.right
            anchors.top: parent.top
            text: cpuModel.cpuClock + "MHz"
            color: "black"
            font.bold: true
            font.family: "Times New Roman"
            font.pixelSize: 8
        }
        
    }


}
