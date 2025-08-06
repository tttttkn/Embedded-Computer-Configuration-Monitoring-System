import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import QtQuick.Shapes 1.12
import QtGraphicalEffects 1.0

Rectangle
{
    anchors.fill: parent
    color: "transparent"
    ColumnLayout {
        anchors.fill: parent
        ListModel{
            id: nameModel
            ListElement {name: "Host name: raspberrypi"}
            ListElement {name: "OS version: Raspberry Pi Os"}
            ListElement {name: "Kernel version: 5.14.2"}
            ListElement {name: "Uptime:"}

        }
        Component {
            id: nameDelegate
            Text {
                id: name
                text: model.name
                font.pixelSize: 20
            }
        }

        ListView
        {
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            anchors.fill: parent
            model: nameModel
            delegate: nameDelegate
            clip: true
            spacing: 5
        }



    }

}


