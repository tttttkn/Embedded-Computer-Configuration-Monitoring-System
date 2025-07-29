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


            Rectangle {
                id: rectangle
                Layout.fillWidth: true
                height: 40
                color: "transparent"
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

                Label {
                    anchors.centerIn: parent
                    text: "GPU"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.top: parent.top
                    anchors.topMargin: 5
                    font.bold: true
                    font.pixelSize: 14
                }
            }

            // Utilization Section
            GroupBox {
                Layout.fillWidth: true
                title: ""
                Canvas {
                    id: gpuCanvas

                    // Danh sách lưu % CPU (0-100)
                    property var gpuData: []
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

                    // Timer cập nhật dữ liệu
                    //Timer {
                    //    interval: 500 // 0.5 giây
                    //    running: true
                    //    repeat: true
                    //    onTriggered: {
                    //        // Thêm dữ liệu ngẫu nhiên (0-100%)
                    //        var newValue = Math.random() * 100;
                    //        gpuCanvas.gpuData.push(newValue);

                    //        // Giới hạn số điểm dữ liệu
                    //        if (gpuCanvas.gpuData.length > gpuCanvas.maxDataPoints) {
                    //            gpuCanvas.gpuData.shift();
                    //        }

                    //        // Yêu cầu vẽ lại
                    //        gpuCanvas.requestPaint();
                    //    }
                    //}
                    Connections {
                        target: modelController
                        onNetworkInfoChanged: {
                            gpuCanvas.gpuData.push((modelController.gpuInfo.clockSpeed / modelController.gpuInfo.clockSpeedMax) * 100);
                            // Giới hạn số điểm dữ liệu
                            if (gpuCanvas.gpuData.length > gpuCanvas.maxDataPoints) {
                                gpuCanvas.gpuData.shift();
                            } 
                            gpuCanvas.requestPaint();
                        }
                    }

                    // Vẽ biểu đồ
                    onPaint: {
                        var ctx = getContext("2d");
                        ctx.reset();

                        // Vẽ lưới
                        ctx.strokeStyle = "black";
                        ctx.lineWidth = 1;

                        // Lưới ngang (10%, 20%,...)
                        for (var y = 0; y <= 100; y += 10) {
                            ctx.beginPath();
                            ctx.moveTo(0, height -10 - y * gridStepY);
                            ctx.lineTo(width - 30, height -10 - y * gridStepY);
                            ctx.stroke();

                            // Nhãn trục Y
//                            ctx.fillStyle = "black";
//                            ctx.font = "10px Arial";
//                            ctx.fillText(y + "%", width-20, height -10 - y * gridStepY + 3);
                        }

                        for (var y = 0; y <= 100; y += 100) {
                            ctx.beginPath();
//                            ctx.moveTo(0, height -10 - y * gridStepY);
//                            ctx.moveTo(width - 30, height -10 - y * gridStepY);


                            // Nhãn trục Y
                            ctx.fillStyle = "black";
                            ctx.font = "10px Arial bold";
                            ctx.fillText(y + "%", width-30, height -10 - y * gridStepY + 3);
                        }

                        // Vẽ đường CPU
                        if (gpuData.length > 0) {
                            ctx.strokeStyle = "blue";
                            ctx.lineWidth = 2;
                            ctx.beginPath();

                            for (var i = 0; i < gpuData.length; i++) {
                                var x = i * gridStepX;
                                var y = height - 10 - gpuData[i] * gridStepY;

                                if (i === 0) {
                                    ctx.moveTo(x, y);
                                } else {
                                    ctx.lineTo(x, y);
                                }
                            }

                            ctx.stroke();
                        }

                        // Vẽ điểm dữ liệu
//                        ctx.fillStyle = "red";
//                        for (var j = 0; j < gpuData.length; j++) {
//                            var pointX = j * gridStepX;
//                            var pointY = height -10 - gpuData[j] * gridStepY;
//                            ctx.beginPath();
//                            ctx.arc(pointX, pointY, 3, 0, Math.PI * 2);
//                            ctx.fill();
//                        }

                    }
                        }
            }

            // Speed Section
            RowLayout {
                Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
                Layout.fillWidth: true
                // Processes Section
                GroupBox {
                    ColumnLayout {
//                        columns: 2
//                        columnSpacing: 2
                        spacing: 1

                        Label {color: "black"; text: "GPU Memmory:" ;font.family: "Times New Roman";Layout.alignment: Qt.AlignLeft;font.pointSize: 10 }
                        Label {color: "black"; text:  modelController.gpuInfo.gpuMemory.toFixed(0) + "MB"; font.bold: true; font.family: "Times New Roman"; Layout.alignment: Qt.AlignRight;font.pointSize: 10 }

                        Label {color: "black"; text: "Clock:";font.family: "Times New Roman";font.pointSize: 10 }
                        Label {color: "black"; text: modelController.gpuInfo.clockSpeed.toFixed(0) + "MHz"; font.bold: true; font.family: "Times New Roman"; Layout.alignment: Qt.AlignRight;font.pointSize: 10 }
                    }
                }
                GroupBox
                {
                    GridLayout {
                        columns: 2
                        columnSpacing: 2
                        rowSpacing: 10
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        Layout.fillHeight: false

                        Label { color: "black"; text: "Utilization:";font.family: "Times New Roman" ; Layout.alignment: Qt.AlignLeft;font.pointSize: 10}
                        Label { text: (modelController.gpuInfo.clockSpeed / modelController.gpuInfo.clockSpeedMax) * 100 + "%"; font.bold: true; font.family: "Times New Roman"; Layout.alignment: Qt.AlignRight;font.pointSize: 10}

                        Label { color: "black"; text: "Temp:";font.family: "Times New Roman" ; Layout.alignment: Qt.AlignLeft;font.pointSize: 10}
                        Label { text: modelController.gpuInfo.temperature.toFixed(1) + "°C"; font.bold: true; font.family: "Times New Roman"; Layout.alignment: Qt.AlignRight;font.pointSize: 10}
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
