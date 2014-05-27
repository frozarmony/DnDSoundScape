import QtQuick 2.0
import QtMultimedia 5.0

Item {
    // Usable Property
	property var	soundModel

	// Style Property
	property int    size:           140
    property color  mainColor:      "#888888"
    property color  baseColor:      "#000000"
	property color  activeColor:    "#008800"
    property color  textColor:      "#FFFFFF"
    property real   ratioCenter:    0.7142857142
    property real   ratioTextImg:   0.2

	// View
	width: size
	height: size

    Rectangle {
		id: body

        radius: 88
        anchors.fill: parent
        gradient: Gradient {
            GradientStop {
                id: topGrad
                position: 0
				color: ((soundModel.isPlaying())? activeColor : baseColor)
            }

            GradientStop {
                position: 0.5
                color: mainColor
            }

            GradientStop {
                id: botGrad
                position: 1
				color: ((soundModel.isPlaying())? activeColor : baseColor)
            }
        }
		border.width: 5

        Text {
			id: name

			text: soundModel.name

            y: size*(1-ratioCenter)*0.5
            width: size*ratioCenter
            height: size*ratioCenter*ratioTextImg
			anchors.horizontalCenter: parent.horizontalCenter
			verticalAlignment: Text.AlignVCenter
			horizontalAlignment: Text.AlignHCenter

			color: textColor
			font.pixelSize: height
            font.family: "Times New Roman"
            font.italic: true
			antialiasing: true
		}

        Image {
			id: image

			source: "file:///" + soundModel.imgPath

            y: size*((1-ratioCenter)*0.5 + ratioCenter*ratioTextImg)
            width: size*ratioCenter
            height: size*ratioCenter*(1-ratioTextImg)
            anchors.horizontalCenter: parent.horizontalCenter

            fillMode: Image.PreserveAspectFit
			antialiasing: true
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
			onClicked: {
				if( soundModel.type == TYPE_PLACE )
					backend.loadPlace(soundModel)
				else if(!soundModel.isPlaying())
					soundModel.start()
				else
					soundModel.stop()
			}
        }
	}

	// Actions onStarted and onStopped of SoundModel
	Connections{
		target: soundModel

		onStarted:	{
			switch(soundModel.type){
			case TYPE_ONE_SHOT:
				oneShotAnimation.start()
				break;
			case TYPE_AMBIANT:
				ambiantStartAnimation.start()
				break;
			case TYPE_MUSIC:
				topGrad.color = activeColor
				botGrad.color = activeColor
				break;
			case TYPE_PLACE:
				ambiantStartAnimation.start()
				break;
			}
		}

		onStopped:	{
			switch(soundModel.type){
			case TYPE_AMBIANT:
				ambiantStopAnimation.start()
				break;
			case TYPE_MUSIC:
				topGrad.color = baseColor
				botGrad.color = baseColor
				break;
			case TYPE_PLACE:
				ambiantStopAnimation.start()
				break;
			}
		}
	}

	// Animations
	SequentialAnimation{
		id: oneShotAnimation
		ColorAnimation { targets: [topGrad, botGrad]; property: "color"; to: activeColor; duration: 50 }
		ColorAnimation { targets: [topGrad, botGrad]; property: "color"; to: baseColor; duration: 50 }
	}

	ColorAnimation { id: ambiantStartAnimation; targets: [topGrad, botGrad]; property: "color"; to: activeColor; duration: 1000 }
	ColorAnimation { id: ambiantStopAnimation; targets: [topGrad, botGrad]; property: "color"; to: baseColor; duration: 1000 }

}
