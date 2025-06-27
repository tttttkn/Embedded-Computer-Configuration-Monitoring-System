import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import QtQuick.Shapes 1.12
import QtGraphicalEffects 1.0  // Hoặc phiên bản thấp hơn tùy Qt version

Rectangle {
//    id: menuBar
    anchors.left: parent.left
    width: 34
    height: parent.height
    color: "transparent"
    radius: 10

    
    ColumnLayout {
        anchors.fill: parent
        spacing: 3
        
        // Nút Cài đặt
        Button {
            id: button
            height: (parent.height-spacing*2) / 3
            Layout.leftMargin: 2
            Layout.topMargin: 2
            width: parent.width
            Layout.fillWidth: true
            Layout.fillHeight: true
            background: Rectangle {
                color: parent.down ? menuPressedColor : "#70786e"
                border.color: "black"
                radius: 10
            }
            Image {
                source: "qrc:/icon/settings_24dp.svg"
                anchors.centerIn: parent
                width: 32
                height: 32
            }
            
            onClicked: {

            }
        }
        
        // Nút Thông báo
        Button {
            height: (parent.height-spacing*2) / 3
            Layout.leftMargin: 2
            width: parent.width
            Layout.fillWidth: true
            Layout.fillHeight: true
            background: Rectangle {
                color: parent.down ? menuPressedColor : "#70786e"
                border.color: "black"
                radius: 10
            }
            
            Image {
                source: "qrc:/icon/notify_24dp.svg"
                anchors.centerIn: parent
                width: 32
                height: 32
            }
            
            
            onClicked: {

            }
        }
        
        // Nút Màn hình chính
        Button {
            id: homeButton
            height: (parent.height-spacing*2) / 3
            Layout.leftMargin: 2
            Layout.bottomMargin: 2
            width: parent.width
            Layout.fillWidth: true
            Layout.fillHeight: true
            background: Rectangle {
                color: parent.down ? menuPressedColor : "#70786e"
                border.color: "black"
                radius: 10
            }
            
            Image {
                source: "qrc:/icon/home_24dp.svg"
                anchors.centerIn: parent
                width: 32
                height: 32
            }
            
            onClicked: {
//                stackView.replace("homePage.qml")
//                stackView.pop(null);
                if (stackView.currentItem !== "homePage.qml")
                {
                    stackView.pop(null);
                }

//                stackView.pop(stackView.get(0));
            }
        }
    }
}
