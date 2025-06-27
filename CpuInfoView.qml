import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import QtQuick.Shapes 1.12
import QtGraphicalEffects 1.0  // Hoặc phiên bản thấp hơn tùy Qt version
import QtQuick.Controls.Styles 1.4
import QtCharts 2.5

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

                Canvas {
                    id: cpuCanvas

                    // Danh sách lưu % CPU (0-100)
                    property var cpuData: []
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
                    Timer {
                        interval: 500 // 0.5 giây
                        running: true
                        repeat: true
                        onTriggered: {
                            // Thêm dữ liệu ngẫu nhiên (0-100%)
                            var newValue = Math.random() * 100;
                            cpuCanvas.cpuData.push(newValue);

                            // Giới hạn số điểm dữ liệu
                            if (cpuCanvas.cpuData.length > cpuCanvas.maxDataPoints) {
                                cpuCanvas.cpuData.shift();
                            }

                            // Yêu cầu vẽ lại
                            cpuCanvas.requestPaint();
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
                        if (cpuData.length > 0) {
                            ctx.strokeStyle = "blue";
                            ctx.lineWidth = 2;
                            ctx.beginPath();

                            for (var i = 0; i < cpuData.length; i++) {
                                var x = i * gridStepX;
                                var y = height - 10 - cpuData[i] * gridStepY;

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

//            GroupBox {
//                id: groupBox
//                height: 150
//                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
//                padding: 0
//                rightPadding: 0
//                bottomPadding: 0
//                leftPadding: 0
//                topPadding: 0
//                Layout.fillWidth: true
//                ChartView {
//                    id: chart
//                    height: 200
//                    anchors.fill: parent
////                    Layout.fillWidth: true
////                    Layout.fillHeight: true
//                    titleColor: "#00000000"
//                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
//                    Layout.fillWidth: true
//                        theme: ChartView.ChartThemeDark
//                        antialiasing: true
//                        legend.visible: false

//                        ValueAxis {
//                            id: axisX

//                            titleText: "Time (s)"
//                        }

//                        ValueAxis {
//                            id: axisY
//                            min: 0
//                            max: 100
//                            titleFont.pointSize: 5
//                            titleText: "CPU Usage (%)"
//                        }

//                        LineSeries {
//                            id: cpuSeries
//                            name: "CPU Usage"
//                            axisX: axisX
//                            axisY: axisY
//                        }

//                        Timer {
//                            interval: 1000
//                            running: true
//                            repeat: true
//                            onTriggered: {
//                                var cpuUsage = CpuReader.getUsage()  // C++ function
//                                cpuSeries.append(xValue++, cpuUsage)
//                                if (xValue > axisX.max) {
//                                    axisX.min += 1
//                                    axisX.max += 1
//                                }
//                            }
//                        }
//                }

//}


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
                        Label {color: "black"; text: "239"; font.pointSize: 10; font.bold: true; font.family: "Times New Roman"; Layout.alignment: Qt.AlignRight }

                        Label {color: "black"; text: "Threads:" ; font.pointSize: 10;font.family: "Times New Roman" }
                        Label {color: "black"; text: "3711"; font.pointSize: 10; font.bold: true; font.family: "Times New Roman"; Layout.alignment: Qt.AlignRight }

                        Label {color: "black"; text: "Cores:" ; font.pointSize: 10;font.family: "Times New Roman" }
                        Label {color: "black"; text: "6"; font.pointSize: 10; font.bold: true; font.family: "Times New Roman"; Layout.alignment: Qt.AlignRight }
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
                        Label { text: "90 %"; font.pointSize: 10; font.bold: true; font.family: "Times New Roman"; Layout.alignment: Qt.AlignRight | Qt.AlignVCenter }

                        Label { color: "black";text: "Clock:"; font.pointSize: 10;font.family: "Times New Roman" }
                        Label { color: "black";text: "2.74 GHz"; font.pointSize: 10; font.family: "Times New Roman"; font.bold: true; Layout.alignment: Qt.AlignRight }

                        Label { color: "black";text: "Temp:"; font.pointSize: 10;font.family: "Times New Roman" }
                        Label {color: "black"; text: cpuModel.cpuTemp + "°C"; font.pointSize: 10; font.bold: true; font.family: "Times New Roman"; Layout.alignment: Qt.AlignRight }
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
