import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import QtQuick.Shapes 1.12
import QtGraphicalEffects 1.0

Rectangle {
    property int frequencyValue: 1
    anchors.fill: parent
    color: "transparent"
    border.color: "black"
    radius: 5
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
                text: "Update frequency"
                font.pixelSize: 14
                Layout.alignment: Qt.AlignLeft
            }

            Item {
                Layout.fillWidth: true
            }

            //SpinBox {
            //    id: updateFrequency
            //    from: 1
            //    to: 60
            //    value: 1
            //    stepSize: 1
            //    editable: true
            //    
            //    // Tùy chỉnh giao diện
            //    Layout.preferredWidth: 40
            //    Layout.preferredHeight: 20
            //    
            //    contentItem: Text {
            //        text: updateFrequency.value + "s"
            //        font: updateFrequency.font
            //        color: "black"
            //        horizontalAlignment: Text.AlignHCenter
            //        verticalAlignment: Text.AlignVCenter
            //    }
            //}

            Rectangle {
                id: frequencyDisplay
                width: 30
                height: 20
                color: "transparent"
                border.color: "#423f3fff"
                radius: 3

                Text {
                    anchors.centerIn: parent
                    text: frequencyValue + "s"
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
                    onClicked: if (frequencyValue < 60) frequencyValue++

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
                    onClicked: if (frequencyValue > 1) frequencyValue--

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

        // Row 2: Dark Mode
        RowLayout {
            spacing: 20
            Layout.fillWidth: true

            Text {
                text: "Dark Mode:"
                font.pixelSize: 14
                Layout.alignment: Qt.AlignLeft
            }
            Item {
                Layout.fillWidth: true
            }

            Switch {
                id: darkModeSwitch
                checked: false
                Layout.alignment: Qt.AlignRight
                // Điều chỉnh kích thước Switch
                implicitWidth: 40  // Giảm chiều rộng
                implicitHeight: 20 // Giảm chiều cao
                
                // Tùy chỉnh phần "nút trượt"
                indicator: Rectangle {
                    implicitWidth: 40
                    implicitHeight: 20
                    radius: 10
                    color: darkModeSwitch.checked ? "#21be2b" : "heavygray"
                    border.color: darkModeSwitch.checked ? "#21be2b" : "#cccccc"
                    
                    Rectangle {
                        x: darkModeSwitch.checked ? parent.width - width : 0
                        width: 20
                        height: 20
                        radius: 10
                        color: darkModeSwitch.down ? "#cccccc" : "#ffffff"
                        border.color: "#999999"
                        Behavior on x { NumberAnimation { duration: 100 } }
                    }
                }
            }
        }

        RowLayout {
            spacing: 20
            Layout.fillWidth: true

            Text {
                text: "Sound Alert"
                font.pixelSize: 14
                Layout.alignment: Qt.AlignLeft
            }

            Item {
                Layout.fillWidth: true
            }

            Switch {
                id: soundAlertSwitch
                checked: true
                Layout.alignment: Qt.AlignRight
                // Điều chỉnh kích thước Switch
                implicitWidth: 40  // Giảm chiều rộng
                implicitHeight: 20 // Giảm chiều cao
                
                // Tùy chỉnh phần "nút trượt"
                indicator: Rectangle {
                    implicitWidth: 40
                    implicitHeight: 20
                    radius: 10
                    color: soundAlertSwitch.checked ? "#21be2b" : "heavygray"
                    border.color: soundAlertSwitch.checked ? "#21be2b" : "#cccccc"
                    
                    Rectangle {
                        x: soundAlertSwitch.checked ? parent.width - width : 0
                        width: 20
                        height: 20
                        radius: 10
                        color: soundAlertSwitch.down ? "#cccccc" : "#ffffff"
                        border.color: "#999999"
                        Behavior on x { NumberAnimation { duration: 100 } }
                    }
                }
            }
        }

        Item {
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

            }
        }
    }
   
    
}