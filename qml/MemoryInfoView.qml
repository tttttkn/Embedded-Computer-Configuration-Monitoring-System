import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import QtQuick.Shapes 1.12
import QtGraphicalEffects 1.0  // Hoặc phiên bản thấp hơn tùy Qt version
import QtQuick.Controls.Styles 1.4

Item {


Rectangle {
    color: "#00000000"
    radius: 10
    border.width: 1
    anchors.rightMargin: 2
    anchors.leftMargin: 2
    anchors.bottomMargin: 2
    anchors.topMargin: 2
        anchors.fill: parent

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 5
            spacing: 5


            // CPU Model Header
            Rectangle {
                id: rectangle
                Layout.fillWidth: true
                height: 40
                color: "transparent"
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

                Label {
                    anchors.centerIn: parent
                    text: "RAM"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.top: parent.top
                    anchors.topMargin: 5
                    font.bold: true
                    font.pixelSize: 14
                }
            }

            // Utilization Section

            RowLayout {
                spacing: 2
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                ColumnLayout {
                    ProgressCircle {
                        id: progress1
                            y: -50
                            lineWidth: 10
                            value: modelController.memoryInfo.ramUsage / 100
                            size: 125
                            secondaryColor: "#585252"
                            primaryColor: "#0787c1"

                            ColorAnimation {
                                from: "white"
                                to: "red"
                                duration: 200
                            }

                            Text {
                                text: parseInt(progress1.value * 100) + "%"
                                anchors.centerIn: parent
                                font.pointSize: 10
                    //            color: progress1.primaryColor
                                color: "black"
                            }
                        }

                    Text {
                        id: ramText
                        text: qsTr("RAM Usage")
                        font.pointSize: 10
                        font.bold: true
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    }
                }

                ColumnLayout {



                GroupBox {
                        id: groupBox
                        topPadding: 12
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                        Layout.fillWidth: true

                        ColumnLayout {

                            spacing: 10
                            anchors.fill: parent
                            RowLayout {
                                Label {
                                    color: "black";
                                    text: "In use:";
                                    font.pointSize: 9;
                                    font.family: "Times New Roman";
                                    Layout.alignment: Qt.AlignLeft }
                                Label {
                                    color: "black";
                                    text: modelController.memoryInfo.usedMemory.toFixed(1);
                                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                                    font.pointSize: 9;
                                    font.bold: true; font.family: "Times New Roman"; }
                            }


                            RowLayout {
                                Label {color: "black"; text: "Available:"; font.pointSize: 9;font.family: "Times New Roman" }
                                Label {color: "black"; text: modelController.memoryInfo.availableMemory.toFixed(1); font.pointSize: 9; font.bold: true; font.family: "Times New Roman"; Layout.alignment: Qt.AlignRight }
                            }
                        }


                    }
                GroupBox {
                    id: groupBox1
                    topPadding: 12
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
                    Layout.fillWidth: true
//                    background: Rectangle {
//                        border.width: 0
//                        color: "transparent"
//                    }
                    ColumnLayout {

                        spacing: 10
                        anchors.fill: parent
                        RowLayout {
                            Label {color: "black"; text: "Swap:"; font.pointSize: 9;font.family: "Times New Roman" }
                            Label {color: "black"; text: modelController.memoryInfo.swapUsage.toFixed(1); font.pointSize: 9; font.bold: true; font.family: "Times New Roman"; Layout.alignment: Qt.AlignRight }
                        }
                        RowLayout {
                            Label {
                                color: "black";
                                text: "In use:";
                                font.pointSize: 9;
                                font.family: "Times New Roman";
                                Layout.alignment: Qt.AlignLeft }
                            Label {
                                color: "black";
                                text: modelController.memoryInfo.swapUsed.toFixed(1);
                                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                                font.pointSize: 9;
                                font.bold: true; font.family: "Times New Roman"; }
                        }


                        RowLayout {
                            Label {color: "black"; text: "Available:"; font.pointSize: 9;font.family: "Times New Roman" }
                            Label {color: "black"; text: modelController.memoryInfo.swapAvailable.toFixed(1); font.pointSize: 9; font.bold: true; font.family: "Times New Roman"; Layout.alignment: Qt.AlignRight }
                        }
                    }

                }


                }
                }












        }
    }

}



/*##^##
Designer {
    D{i:0;autoSize:true;height:240;width:320}
}
##^##*/
