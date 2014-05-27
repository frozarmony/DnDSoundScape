import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1

Rectangle{
    id: soundController

	// Model
	property var masterVolumeModel

    // Property
    property string name: "Name Test"
    property color controllerColor: "#004400"
	property int fontSize: 18

	width: 100
	height: 240
	color: "#00000000"

	Image {
		id: background
		anchors.fill: parent
		source: "img/sliderBackground.png"
	}

	Rectangle{
        id: volumeName
		y: 15

        width: parent.width
        height: fontSize + 4
		color: "#00000000"

        Text {
            text: name
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

            anchors.fill: parent
            font.pixelSize: fontSize
        }
    }

    Slider {
        id: slider

        maximumValue: 1.0
        minimumValue: 0.0
		value: masterVolumeModel.volume

        orientation: 0
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.bottom: parent.bottom
		anchors.bottomMargin: 15
		anchors.top: volumeName.bottom
		anchors.topMargin: 10

		style: SliderStyle {

			handle: Image{
				source: control.pressed ? "img/slider-handle-on.png" : "img/slider-handle-off.png"
			}
		}
    }

	Connections{
		target: slider
		onValueChanged: masterVolumeModel.volume = slider.value
	}


}
