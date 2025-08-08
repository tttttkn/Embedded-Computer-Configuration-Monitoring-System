import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


Rectangle
{
    anchors.fill: parent
    color: "transparent"

// Our log model
    ListModel {
        id: logModel
    }

    // Function to add new log entries
    function addLogEntry(level, message, timestamp = new Date().toLocaleTimeString(Qt.locale(), "HH:mm:ss")) {
        logModel.append({
            "level": level,
            "message": message,
            "timestamp": timestamp
        })
        // Auto-scroll to bottom
        logListView.positionViewAtEnd()
    }



    ColumnLayout {
        anchors.fill: parent
        spacing: 5

        RowLayout {
            Button {
                text: "Clear Logs"
                onClicked: logModel.clear()
            }
            Button {
                text: "Test Message"
                onClicked: addLogEntry("WARNING", "This is a test log message and you dont want to hide me")
            }
        }

        Connections {
            target: logger
            onNewLogChanged: {
                console.log("QML: newLogChanged signal received")
                console.log("QML: new log value:", logger.newLog)
                addLogEntry("WARNING", logger.newLog)
            }
        }

        ListView {
            id: logListView
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: logModel
            spacing: 2

            delegate: Rectangle {
                id: rectangle
                width: parent.width
                height: logText.height
                color: "#eaeaaa"

                border.color: "#85aae5"
                radius: 5

                Text {
                    id: logText
                    text: "["+ timestamp + "]: " + message
                    width: parent.width
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }

            }


            ScrollBar.vertical: ScrollBar {}
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
