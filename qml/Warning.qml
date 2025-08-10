import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import QtQuick.Shapes 1.12
import QtGraphicalEffects 1.0

Rectangle {
    property int cpuWarn: modelController.cpuWarn
    property int cpuCrit: modelController.cpuCrit
    property int ramWarn: modelController.ramWarn

    anchors.fill: parent
    color: "transparent"
    border.color: "black"
    radius: 5

    Popup {
        id: confirmPopup
        width: 200
        height: 100
        anchors.centerIn: parent
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        background: Rectangle
        {
            radius: 5
            color: "#f0f0f0"  
            border.color: "#3498db" 
            border.width: 2 
        }

        ColumnLayout {
            anchors.fill: parent
            spacing: 10
            
            Text {
                text: "Save?"
                font.pixelSize: 16
                Layout.alignment: Qt.AlignHCenter
                color: "#333333"  // Màu chữ đậm hơn
            }
            
            RowLayout {
                Layout.alignment: Qt.AlignHCenter
                spacing: 20
                
                Button {
                    text: "OK"
                    font.pixelSize: 16
                    Layout.preferredWidth: 70
                    background: Rectangle
                    {
                        radius: 5
                        color: parent.down ? "#27ae60" : "#2ecc71"  // Xanh lá cây
                        border.color: "#27ae60"
                        border.width: 1
                    }
                    contentItem: Text {
                        text: parent.text
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    onClicked: {
                        modelController.setCpuWarn(cpuWarn)
                        modelController.setCpuCrit(cpuCrit)
                        modelController.setRamWarn(ramWarn)
                        confirmPopup.close()
                    }
                }
                
                Button {
                    text: "Cancel"
                    Layout.preferredWidth: 70
                    background: Rectangle {
                        radius: 5
                        color: parent.down ? "#e74c3c" : "#ec7063"  // Đỏ
                        border.color: "#e74c3c"
                        border.width: 1
                    }
                    
                    contentItem: Text {
                        text: parent.text
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    onClicked: confirmPopup.close()
                }
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.leftMargin: 15
        anchors.rightMargin: 15
        anchors.topMargin: 5
        anchors.bottomMargin: 5
        spacing: 2
    
        RowLayout {
            spacing: 5
            Layout.fillWidth: true

            Text {
                text: "CPU Warn (%)"
                font.pixelSize: 14
                Layout.alignment: Qt.AlignLeft
            }

            Item {
                Layout.fillWidth: true
            }

            Rectangle {
                id: cpuWarnDisplay
                width: 30
                height: 20
                color: "transparent"
                border.color: "#423f3fff"
                radius: 3

                Text {
                    anchors.centerIn: parent
                    text: cpuWarn + "%"
                    font.pixelSize: 12
                    color: "black"
                }
            }

            Column {
                spacing: 1

                // Nút mũi tên lên
                Button {
                    width: 20
                    height: 10
                    onClicked: if (cpuWarn < cpuCrit) cpuWarn++

                    background: Rectangle {
                        color: parent.down ? "#dddddd" : "grey"
                        border.color: "#3f3b3bff"
                        radius: 2
                    }

                    contentItem: Text {
                        text: "▲"
                        font.pixelSize: 7
                        color: "black"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                // Nút mũi tên xuống
                Button {
                    width: 20
                    height: 10
                    onClicked: if (cpuWarn > 50) cpuWarn--

                    background: Rectangle {
                        color: parent.down ? "#dddddd" : "grey"
                        border.color: "#3f3b3bff"
                        radius: 2
                    }

                    contentItem: Text {
                        text: "▼"
                        font.pixelSize: 7
                        color: "black"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }

        }
        RowLayout {
            spacing: 5
            Layout.fillWidth: true

            Text {
                text: "CPU Crit (%)"
                font.pixelSize: 14
                Layout.alignment: Qt.AlignLeft
            }

            Item {
                Layout.fillWidth: true
            }

            Rectangle {
                id: cpuCritDisplay
                width: 30
                height: 20
                color: "transparent"
                border.color: "#423f3fff"
                radius: 3

                Text {
                    anchors.centerIn: parent
                    text: cpuCrit + "%"
                    font.pixelSize: 12
                    color: "black"
                }
            }

            Column {
                spacing: 1

                // Nút mũi tên lên
                Button {
                    width: 20
                    height: 10
                    onClicked: if (cpuCrit < 99) cpuCrit++

                    background: Rectangle {
                        color: parent.down ? "#dddddd" : "grey"
                        border.color: "#3f3b3bff"
                        radius: 2
                    }

                    contentItem: Text {
                        text: "▲"
                        font.pixelSize: 7
                        color: "black"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                // Nút mũi tên xuống
                Button {
                    width: 20
                    height: 10
                    onClicked: if (cpuCrit > cpuWarn) cpuCrit--

                    background: Rectangle {
                        color: parent.down ? "#dddddd" : "grey"
                        border.color: "#3f3b3bff"
                        radius: 2
                    }

                    contentItem: Text {
                        text: "▼"
                        font.pixelSize: 7
                        color: "black"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }

        }
        RowLayout {
            spacing: 5
            Layout.fillWidth: true

            Text {
                text: "RAM Warn (%)"
                font.pixelSize: 14
                Layout.alignment: Qt.AlignLeft
            }

            Item {
                Layout.fillWidth: true
            }

            Rectangle {
                id: ramWarnDisplay
                width: 30
                height: 20
                color: "transparent"
                border.color: "#423f3fff"
                radius: 3

                Text {
                    anchors.centerIn: parent
                    text: ramWarn + "%"
                    font.pixelSize: 12
                    color: "black"
                }
            }

            Column {
                spacing: 1

                // Nút mũi tên lên
                Button {
                    width: 20
                    height: 10
                    onClicked: if (ramWarn < 99) ramWarn++

                    background: Rectangle {
                        color: parent.down ? "#dddddd" : "grey"
                        border.color: "#3f3b3bff"
                        radius: 2
                    }

                    contentItem: Text {
                        text: "▲"
                        font.pixelSize: 7
                        color: "black"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                // Nút mũi tên xuống
                Button {
                    width: 20
                    height: 10
                    onClicked: if (ramWarn > 50) ramWarn--

                    background: Rectangle {
                        color: parent.down ? "#dddddd" : "grey"
                        border.color: "#3f3b3bff"
                        radius: 2
                    }

                    contentItem: Text {
                        text: "▼"
                        font.pixelSize: 7
                        color: "black"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }

        }
        Item
        {
            Layout.fillHeight: true
        }

        Button {
            id: saveButton
            text: "Save settings"
            font.pixelSize: 14
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 200
            Layout.preferredHeight: 40

            background: Rectangle {
                radius: 5
                color: parent.down ? "#3498db" : "#2980b9"
            }

            contentItem: Text {
                text: parent.text
                font: parent.font
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            onClicked: {
                confirmPopup.open()
            }
        }
    }
    
}