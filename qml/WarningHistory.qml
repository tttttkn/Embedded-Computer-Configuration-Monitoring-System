import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Rectangle {
    anchors.fill: parent
    color: "transparent"
    anchors.margins: 2

    ListModel {
        id: alert
    }

    // Function to add new log entries
    function addAlert(type, message, timestamp = new Date().toLocaleTimeString(Qt.locale(), "HH:mm:ss")) {
        alert.append({
            "type": type,
            "message": message,
            "timestamp": timestamp
        })
        // Auto-scroll to bottom
        alertListView.positionViewAtEnd()
    }



    ColumnLayout {
        anchors.fill: parent
        spacing: 5

        Connections {
            target: alertModel
            onNewAlertChanged: {
                console.log("QML: newLogChanged signal received")
                console.log("QML: new log value:", alertModel.newAlert.message)
                console.log("QML: new log value:", alertModel.newAlert.type)

                addAlert(alertModel.newAlert.type, alertModel.newAlert.message)
            }
        }

        ListView {
            id: alertListView
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: alert
            spacing: 2

            delegate: Rectangle {
                id: rectangle
                width: parent.width
                height: alertText.height
                //color: "#eaeaaa"
                //color: {
                //    if (model.type === "CRITICAL") "#ffeeee"
                //    else if (model.type === "WARNING") "#fff8e8"
                //    else "white"
                //}
                color: "transparent"

                border.color: "#85aae5"
                radius: 3

                Text {
                    id: alertText
                    text: "["+ timestamp + "]: " + message
                    width: parent.width
                    color: model.type === "CRITICAL" ? "#cc0000" : "#ff9900"

                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }

            }


            ScrollBar.vertical: ScrollBar {}
        }
        // Nút Xóa Tất Cả
        Button {
            text: "Delete all"
            Layout.alignment: Qt.AlignHCenter
            Layout.bottomMargin: 10
            Layout.preferredWidth: 120
            Layout.preferredHeight: 40

            background: Rectangle {
                radius: 5
                color: parent.down ? "#d9534f" : "#e74c3c"
            }

            contentItem: Text {
                text: parent.text
                color: "white"
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            onClicked: {
                alert.clear()
            }
        }
    }
}



/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
