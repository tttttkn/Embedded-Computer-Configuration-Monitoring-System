import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Rectangle {
    id: systemSetting
    anchors.fill: parent
    anchors.margins: 2
    color: "transparent"


    ColumnLayout {
        anchors.fill: parent
        spacing: 2
        TabBar {
            id: tabBar
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            Layout.fillWidth: true
            background: Rectangle {
                color: "transparent"
            }

            TabButton {
                text: "System"
                display: AbstractButton.TextOnly

                contentItem: Text {
                    text: parent.text
                    font.bold: true
                    color: tabBar.currentIndex === 0 ? "#225cba" : "black" // Màu khi chọn/không chọn
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                background: Rectangle {
                    radius: 5
                    border.width: 1
                    color: tabBar.currentIndex === 0 ? "#EAF0FA" : "transparent"
                }
            }
            TabButton {
                text: "Track"
                contentItem: Text {
                    text: parent.text
                    font.bold: true
                    color: tabBar.currentIndex === 1 ? "#225cba" : "black" // Màu khi chọn/không chọn
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                background: Rectangle {
                    radius: 5
                    border.width: 1
                    color: tabBar.currentIndex === 1 ? "#EAF0FA" : "transparent"
                }
            }
            TabButton {
                text: "Notify"
                contentItem: Text {
                    text: parent.text
                    font.bold: true
                    color: tabBar.currentIndex === 2 ? "#225cba" : "black" // Màu khi chọn/không chọn
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                background: Rectangle {
                    radius: 5
                    border.width: 1
                    color: tabBar.currentIndex === 2 ? "#EAF0FA" : "transparent"
                }
            }
            TabButton {
                text: "Logs"
                contentItem: Text {
                    text: parent.text
                    font.bold: true
                    color: tabBar.currentIndex === 3 ? "#225cba" : "black" // Màu khi chọn/không chọn
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                background: Rectangle {
                    radius: 5
                    border.width: 1
                    color: tabBar.currentIndex === 3 ? "#EAF0FA" : "transparent"
                }
            }
        }


        StackLayout {
                    id: stackLayout
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    currentIndex: tabBar.currentIndex // Liên kết 2 chiều

                    System{}

                    // Nội dung Tab 2
                    Rectangle {
                        color: "transparent"
                        Text { anchors.centerIn: parent; text: "Nội dung Tab 2"; font.bold: true }
                    }

                    // Nội dung Tab 3
                    Rectangle {
                        color: "transparent"
                        Text { anchors.centerIn: parent; text: "Nội dung Tab 3"; font.bold: true }
                    }

                    Logs{}
                }
    }
}



/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
