import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import QtQuick.Shapes 1.12
import QtGraphicalEffects 1.0  // Hoặc phiên bản thấp hơn tùy Qt version

Button {
//    id: gpuButton
    anchors.right: parent.right
    anchors.leftMargin: 2
    anchors.topMargin: 2
    anchors.rightMargin: 2
    anchors.bottomMargin: 2
    width: (parent.width  - spacing) / 2
    height: (parent.height - spacing) / 2
    anchors.top: parent.top

    background: Rectangle {
        color: parent.down ? buttonPressedColor : "transparent"
        border.color: "black"
        radius: 10
    }
    Text {
        id: gpuText
        width: wrapMode
        height: wrapMode
        color: "black"
        x: 5
        text: qsTr("GPU MOD")
        font.family: "Times New Roman"
        font.bold: true
        font.pixelSize: 16
        anchors.verticalCenter: parent.top
        anchors.verticalCenterOffset: parent.height * (1/10)

    }

    ProgressCircle {
        id: progress1
        lineWidth: 10
        value: 0.9
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
        width: 50  // Rộng hơn để đẹp hơn
        height: 8    // Chiều cao mỏng, hiện đại

        value: 0.5   // Giá trị tiến trình



        background: Rectangle {
            implicitWidth: 200
            implicitHeight: 8
            color: "#555a61"       // Màu nền sáng hơn
            radius: height/2        // Bo tròn hoàn toàn
            border.color: "#000000" // Viền nhẹ
            border.width: 1



        }

        contentItem: Item {
            implicitWidth: 200
            implicitHeight: 8

            Rectangle {
                width: control.visualPosition * parent.width
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
                // Bo tròn tương tự background
            }
        }
    }

    ProgressBar {
        id: control1
        x: 82
        y: 70
        width: 50  // Rộng hơn để đẹp hơn
        height: 8    // Chiều cao mỏng, hiện đại

        value: 0.5   // Giá trị tiến trình

        background: Rectangle {
            implicitWidth: 200
            implicitHeight: 8
            color: "#555a61"       // Màu nền sáng hơn
            radius: height/2        // Bo tròn hoàn toàn
            border.color: "#000000" // Viền nhẹ
            border.width: 1



        }

        contentItem: Item {
            x: 0
            implicitWidth: 200
            implicitHeight: 8

            Rectangle {
                width: control.visualPosition * parent.width
                height: parent.height
                color: "#4facfe"
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
            text: qsTr("45°C")
            color: "black"
            font.bold: true
            font.family: "Times New Roman"
            font.pixelSize: 8
        }

    }

    Rectangle {
        id: mem
        x: 78
        y: 79

        color: "transparent"
        width: 58
        height: 10
        Text {
            id: clockText
            anchors.left: parent.left
            anchors.top: parent.top
            text: qsTr("MEM")
            color: "black"
            font.bold: true
            font.family: "Times New Roman"
            font.pixelSize: 8
        }

        Text {
            id: clockValue
            anchors.right: parent.right
            anchors.top: parent.top
            text: qsTr("4,5 GB")
            color: "black"
            font.bold: true
            font.family: "Times New Roman"
            font.pixelSize: 8
        }

    }
    
}
