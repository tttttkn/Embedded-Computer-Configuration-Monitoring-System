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
                    text: "NETWORK"
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
                    id: cpuCanvas

                    // Danh sách lưu % CPU (0-100)
                    property var receiveSpeedData: []
                    property var sendSpeedData: []
                    // Kích thước lưới
                    property int maxDataPoints: 20
                    property int gridStepX: (width-30) / maxDataPoints

                    property int gridStepY: (height - 20) / 100
                    x: 50
                    y: 25
                    width: 200
                    height: 120
                    anchors.verticalCenterOffset: 0
                    anchors.horizontalCenterOffset: 0
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
                            var newValue1 = Math.random() * 100;
                            cpuCanvas.receiveSpeedData.push(newValue);
                            cpuCanvas.sendSpeedData.push(newValue1);
                            // Giới hạn số điểm dữ liệu
                            if (cpuCanvas.receiveSpeedData.length > cpuCanvas.maxDataPoints) {
                                cpuCanvas.receiveSpeedData.shift();
                                cpuCanvas.sendSpeedData.shift();
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
                            ctx.fillText(y + "Kbps", width-30, height -10 - y * gridStepY + 3);
                        }

                        // Vẽ đường
                        if (sendSpeedData.length > 0) {
                            ctx.strokeStyle = "blue";
                            ctx.lineWidth = 2;
                            ctx.beginPath();

                            for (var i = 0; i < sendSpeedData.length; i++) {
                                var x = i * gridStepX;
                                var y = height - 10 - sendSpeedData[i] * gridStepY;

                                if (i === 0) {
                                    ctx.moveTo(x, y);
                                } else {
                                    ctx.lineTo(x, y);
                                }
                            }

                            ctx.stroke();
                        }

                        if (receiveSpeedData.length > 0) {
                            ctx.strokeStyle = "red";
                            ctx.lineWidth = 2;
                            ctx.beginPath();

                            for (var i = 0; i < receiveSpeedData.length; i++) {
                                var x = i * gridStepX;
                                var y = height - 10 - receiveSpeedData[i] * gridStepY;

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
//                        for (var j = 0; j < cpuData.length; j++) {
//                            var pointX = j * gridStepX;
//                            var pointY = height -10 - cpuData[j] * gridStepY;
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
                    GridLayout {
                        columns: 2
                        columnSpacing: 2
                        rowSpacing: 2

                        Label {color: "red"; text: "Send:";font.family: "Times New Roman" }
                        Label {color: "red"; text: "239 Kbps"; font.bold: true; font.family: "Times New Roman"; Layout.alignment: Qt.AlignRight }

                        Label {color: "blue"; text: "Receive:" ;font.family: "Times New Roman" }
                        Label {color: "blue"; text: "3711 Kbps"; font.bold: true; font.family: "Times New Roman"; Layout.alignment: Qt.AlignRight }
                    }
                }
                GroupBox
                {
                    GridLayout {
                        columns: 2
                        columnSpacing: 2
                        rowSpacing: 2
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        Layout.fillHeight: false

                        Label { color: "black"; text: "SSID:";font.family: "Times New Roman" }
                        Label { text: "Tan Tai Kieu"; font.bold: true; font.family: "Times New Roman"; Layout.alignment: Qt.AlignRight | Qt.AlignVCenter }

                        Label { color: "black";text: "IPv4:";font.family: "Times New Roman" }
                        Label { color: "black";text: "191.168.2.23"; font.family: "Times New Roman"; font.bold: true; Layout.alignment: Qt.AlignRight }

                        Label { color: "black";text: "Band:";font.family: "Times New Roman" }
                        Label {color: "black"; text: "2.4 GHz"; font.bold: true; font.family: "Times New Roman"; Layout.alignment: Qt.AlignRight }
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
