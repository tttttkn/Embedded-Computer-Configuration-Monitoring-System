import QtQuick 2.9

Item {
    id: root

    property int size: 150
    property int lineWidth: 5
    property real value: 0

    property color primaryColor: "#29b6f6"
    property color secondaryColor: "#e0e0e0"
    property color targetColor: "#C83F12"
    property int animationDuration: 500

    width: size
    height: size

    onValueChanged: {
        canvas.degree = value * 360;
    }

    Canvas {
        id: canvas

        property real degree: value * 360

        anchors.fill: parent
        antialiasing: true

        onDegreeChanged: {
            requestPaint();
        }

        onPaint: {
            var ctx = getContext("2d");

            var x = root.width/2;
            var y = root.height/2;

            var radius = root.size/2 - root.lineWidth
            var startAngle = (Math.PI/180) * 270;
            var fullAngle = (Math.PI/180) * (270 + 360);
            var progressAngle = (Math.PI/180) * (270 + degree);

            ctx.reset()

            ctx.lineCap = 'round';
            ctx.lineWidth = root.lineWidth;

            ctx.beginPath();
            ctx.arc(x, y, radius, startAngle, fullAngle);
            ctx.strokeStyle = root.secondaryColor;
            ctx.stroke();

            ctx.beginPath();
            ctx.arc(x, y, radius, startAngle, progressAngle);
            if (value < 0.75)
            {
                ctx.strokeStyle = root.primaryColor;
            }
            else
            {
                ctx.strokeStyle = targetColor;
            }


            ctx.stroke();
        }

        Behavior on degree {
            NumberAnimation {
                duration: root.animationDuration
                easing.type: Easing.InOutQuad  // Hiệu ứng easing mượt mà
            }

        }
    }
}
