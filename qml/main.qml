import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12

Window {
    id: window
    visible: true
    width: 320
    height: 240
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width
    color: "#cacaca"
    title: "System Dashboard"

    property color buttonColor: "#3498db"
    property color buttonPressedColor: "#2980b9"
    property color menuColor: "#70786e"
    property color menuPressedColor: "#34495e"

    Rectangle {
        id: root
        anchors.fill: parent
        color: "transparent"

        RowLayout {
            anchors.fill: parent
            spacing: 0

            // Vertical Tab Bar - 34px width
            Rectangle {
                id: sideBar
                Layout.fillHeight: true
                Layout.preferredWidth: 34
                color: "transparent"

                ColumnLayout {
                    anchors.fill: parent
                    spacing: 2
                    anchors.leftMargin: 1
                    anchors.topMargin: 2
                    anchors.bottomMargin: 2

                    // Home Tab
                    TabButton {
                        Layout.fillHeight: true
                        Layout.preferredWidth: sideBar.width
                        
                        background: Rectangle {
                            color: 
                            {
                                parent.down ? buttonColor : "#70786e"
                                stackLayout.currentIndex === 0 ? menuPressedColor : menuColor
                            }
                            border.color: "black"
                            radius: 10
                        }

                        Image {
                            source: "qrc:/assets/image/home_24dp.svg"
                            anchors.centerIn: parent
                        width: 32
                        height: 32
                        }

                        onClicked:
                        {
                            stackLayout.currentIndex = 0
                            stackView.pop()

                        } 
                            
                    }

                    // Settings Tab
                    TabButton {
                        Layout.fillHeight: true
                        Layout.preferredWidth: sideBar.width
                        
                        background: Rectangle {
                            color: stackLayout.currentIndex === 1 ? menuPressedColor : menuColor
                            border.color: "black"
                            radius: 10
                        }

                        Image {
                            source: "qrc:/assets/image/settings_24dp.svg"
                            anchors.centerIn: parent
                        width: 32
                        height: 32
                        }

                        onClicked: stackLayout.currentIndex = 1
                    }

                    // Notification Tab
                    TabButton {
                        Layout.fillHeight: true
                        Layout.preferredWidth: sideBar.width
                        
                        background: Rectangle {
                            color: stackLayout.currentIndex === 2 ? menuPressedColor : menuColor
                            border.color: "black"
                            radius: 10
                        }

                        Image {
                            source: "qrc:/assets/image/notify_24dp.svg"
                            anchors.centerIn: parent
                        width: 32
                        height: 32
                        }

                        onClicked: stackLayout.currentIndex = 2
                    }
                }
            }

            // Content Area
            StackLayout {
                id: stackLayout
                Layout.fillWidth: true
                Layout.fillHeight: true
                currentIndex: 0

                StackView {
                    id: stackView
                    initialItem: Qt.resolvedUrl("HomeGadget.qml")
                }

                Connections {
                    target: navigator
                    onViewChanged: {
                    stackView.push(targetUrl)
                    }
                }
                Setting{}
                
                Rectangle {
                    color: "transparent"
                    Label {
                        anchors.centerIn: parent
                        text: "TBD"
                        font.pixelSize: 24
                    }
                }
            }
        }
    }


 
}