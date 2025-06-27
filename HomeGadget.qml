import QtQuick 2.0
import QtQuick.Controls 2.12

//Item {
//    id: homePage


    Rectangle {
//        id: homeScreen
        anchors.fill: parent
        color: "transparent"
        CpuGadget {
            onClicked: stackView.push("CpuInfoView.qml")
        }

        GpuGadget {
            id: gpuButton
            onClicked: stackView.push("GpuInfoView.qml")
        }

        MemoryGadget {
            id: ramButton
            width: 80
            onClicked: stackView.push("MemoryInfoView.qml")
        }

        StorageNetworkGadget {
            id: hddnetButton
            onClicked: stackView.push("NetworkInfoView.qml")
        }

        DateTimeGadget {
            id: datetime
        }
    }

//    StackView {
//        id: homeStackView
//        anchors.fill: parent
//        initialItem: homeScreen // Trang đầu tiên
//    }


//}




//Item {
//    id: root
//    width: 400
//    height: 300


//    Loader {
//        id: screenLoader
//        anchors.fill: parent
//        sourceComponent: currentScreen === "main" ? mainScreen : secondScreen
//    }

//    states: [
//        State {
//            name: "main"
//            when: root.currentScreen === "main"
//        },
//        State {
//            name: "second"
//            when: root.currentScreen === "second"
//        }
//    ]

//    transitions: [
//        Transition {
//            from: "main"
//            to: "second"
//            NumberAnimation { properties: "opacity"; duration: 300 }
//        },
//        Transition {
//            from: "second"
//            to: "main"
//            NumberAnimation { properties: "opacity"; duration: 300 }
//        }
//    ]


//}


/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
