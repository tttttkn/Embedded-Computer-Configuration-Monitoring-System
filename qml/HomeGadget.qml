import QtQuick 2.0
import QtQuick.Controls 2.12

    Rectangle {
        id: homeScreen
        anchors.fill: parent
        color: "transparent"


        CpuGadget {
            onClicked: navigator.requestViewChange("HomeGadget.qml", "CpuInfoView.qml")
        }

        GpuGadget {
            id: gpuButton
            onClicked: navigator.requestViewChange("HomeGadget.qml", "GpuInfoView.qml")
        }

        MemoryGadget {
            id: ramButton
            width: 80
            onClicked: navigator.requestViewChange("HomeGadget.qml", "MemoryInfoView.qml")
        }

        StorageNetworkGadget {
            id: hddnetButton
            onClicked: navigator.requestViewChange("HomeGadget.qml", "NetworkInfoView.qml")
        }

        DateTimeGadget {
            id: datetime
        }

 
    }












/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
