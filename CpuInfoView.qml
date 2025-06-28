import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import QtQuick.Shapes 1.12
import QtGraphicalEffects 1.0 
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
                    text: "CPU"
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.bold: true
                    font.pixelSize: 14
                }
            }

            // Utilization Section
            GroupBox {
                Layout.fillWidth: true
                background: Rectangle {
                    color: "#00000000"
                    border.color: "#00000000"
                }

                //Connections {
                //    target: cpuModel
                //    onCpuUsageChanged: {
                //        cpuCanvas.requestPaint();
                //    }
                //}

                Canvas {
                    id: cpuCanvas

                    // Danh sách lưu % CPU (0-100)
                    //property var cpuModel.cpuUsage: cpuModel.cpuUsage
                    // Kích thước lưới
                    property int maxDataPoints: 20
                    property int gridStepX: (width-30) / maxDataPoints

                    property int gridStepY: (height - 20) / 100
                    x: 50
                    y: 25
                    width: 200
                    height: 120
                    contextType: qsTr("")
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter

                    //Timer {
                    //    interval: 1000 // 0.5 giây
                    //    running: true
                    //    repeat: true
                    //    onTriggered: {
                    //        cpuCanvas.requestPaint();
                    //    }
                    //}


                    Connections {
                        target: cpuModel
                        onCpuUsageChanged: {
                        cpuCanvas.requestPaint();
                    }
                    }
                    onPaint: {
                        var ctx = getContext("2d");
                        ctx.reset();

                        // Vẽ lưới
                        ctx.strokeStyle = "black";
                        ctx.lineWidth = 1;

                        for (var y = 0; y <= 100; y += 10) {
                            ctx.beginPath();
                            ctx.moveTo(0, height -10 - y * gridStepY);
                            ctx.lineTo(width - 30, height -10 - y * gridStepY);
                            ctx.stroke();
                        }

                        for (var y = 0; y <= 100; y += 100) {
                            ctx.beginPath();
//                            ctx.moveTo(0, height -10 - y * gridStepY);
//                            ctx.moveTo(width - 30, height -10 - y * gridStepY);


                            // Nhãn trục Y
                            ctx.fillStyle = "black";
                            ctx.font = "10px Arial";
                            ctx.fillText(y + "%", width-30, height -10 - y * gridStepY + 3);
                        }

                        // Vẽ đường CPU
                        if (cpuModel.cpuUsage.length > 0) {
                            ctx.strokeStyle = "blue";
                            ctx.lineWidth = 2;
                            ctx.beginPath();

                            for (var i = 0; i < cpuModel.cpuUsage.length; i++) {
                                var x = i * gridStepX;
                                var y = height - 10 - cpuModel.cpuUsage[i] * gridStepY;

                                if (i === 0) {
                                    ctx.moveTo(x, y);
                                } else {
                                    ctx.lineTo(x, y);
                                }
                            }

                            ctx.stroke();
                        }


                    }
                        }
            }


            // Speed Section
            RowLayout {
                Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
                Layout.fillWidth: true
                // Processes Section
                GroupBox {
                    padding: 5
                    GridLayout {
                        columns: 2
                        columnSpacing: 2
                        rowSpacing: 2

                        Label {color: "black"; text: "Processes:" ; font.pointSize: 10;font.family: "Times New Roman" }
                        Label {color: "black"; text: cpuModel.totalProcesses; font.pointSize: 10; font.bold: true; font.family: "Times New Roman"; Layout.alignment: Qt.AlignRight }

                        Label {color: "black"; text: "Threads:" ; font.pointSize: 10;font.family: "Times New Roman" }
                        Label {color: "black"; text: cpuModel.totalThreads; font.pointSize: 10; font.bold: true; font.family: "Times New Roman"; Layout.alignment: Qt.AlignRight }

                        Label {color: "black"; text: "Cores:" ; font.pointSize: 10;font.family: "Times New Roman" }
                        Label {color: "black"; text: "1"; font.pointSize: 10; font.bold: true; font.family: "Times New Roman"; Layout.alignment: Qt.AlignRight }
                    }
                }
                GroupBox
                {
                    padding: 5
                    GridLayout {
                        columns: 2
                        columnSpacing: 2
                        rowSpacing: 2
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        Layout.fillHeight: false

                        Label { color: "black"; text: "Utilization:"; font.pointSize: 10;font.family: "Times New Roman" }
                        Label { text: cpuModel.lastCpuUsage.toFixed(1) + "%"; font.pointSize: 10; font.bold: true; font.family: "Times New Roman"; Layout.alignment: Qt.AlignRight | Qt.AlignVCenter }

                        Label { color: "black";text: "Clock:"; font.pointSize: 10;font.family: "Times New Roman" }
                        Label { color: "black";text: cpuModel.cpuClock.toFixed(0) + "MHz"; font.pointSize: 10; font.family: "Times New Roman"; font.bold: true; Layout.alignment: Qt.AlignRight }

                        Label { color: "black";text: "Temp:"; font.pointSize: 10;font.family: "Times New Roman" }
                        Label {color: "black"; text: cpuModel.cpuTemp.toFixed(1) + "°C"; font.pointSize: 10; font.bold: true; font.family: "Times New Roman"; Layout.alignment: Qt.AlignRight }
                    }
                }



            }





        }
    }

}



/*##^##
Designer {
    D{i:0;autoSize:true;height:240;width:320}D{i:2;anchors_width:641;anchors_x:253;anchors_y:34}
}
##^##*/
