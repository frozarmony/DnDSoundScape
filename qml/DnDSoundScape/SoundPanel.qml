import QtQuick 2.0

Rectangle {
	id: panel
	// Model Property
	property var panelModel

	// Property
	property int rowCount: panelModel.rowWidth
	property int titleSize: 50
    property int soundBlockSize:  100
	property int marginGridView: 15
	property int spacing: 3

	// View
    width: 680
	height: titleSize + 2*marginGridView + rowCount*(soundBlockSize+2*spacing)
	opacity: (soundGrid.count===0)?0:1

	// View Animation
	Behavior on opacity { PropertyAnimation{ duration: 1000 } }

    Rectangle{
        id: titleRect

        height: titleSize
		color: "#000000"
		border.width: 2
		anchors.bottom: soundRect.top
		anchors.right: parent.right
		anchors.left: parent.left
		anchors.top: parent.top
		gradient: Gradient {
			GradientStop {
				position: 0
				color: "#000000"
			}

			GradientStop {
				position: 0.323
				color: "#7a5610"
			}

			GradientStop {
				position: 0.681
				color: "#7a5610"
			}

			GradientStop {
				position: 1
				color: "#000000"
			}
		}

        Text {
            id: title
			color: "#bfbca1"
            anchors.fill: parent
            anchors.leftMargin: 20
            font.pixelSize: titleSize*0.8
			text: panelModel.name
			style: Text.Sunken
			font.family: "Times New Roman"
            font.italic: true
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
        }
    }


	Rectangle{
		id: soundRect

        anchors.top: titleRect.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
		anchors.left: parent.left

        Image {
            id: soundBackground

			anchors.fill: parent
			fillMode: Image.Stretch

			source: "img/background-parchemin.jpg"
		}

		GridView {
			id: soundGrid

			model: panelModel
			delegate: Item{
				width: soundBlockSize+2*spacing
				height: soundBlockSize+2*spacing

				SoundBlock{
					soundModel: sound
					size: soundBlockSize
					anchors.centerIn: parent
				}
			}

			anchors.fill: parent
			anchors.margins: marginGridView
			clip: true
			flow: GridView.TopToBottom
			cellWidth: soundBlockSize+2*spacing
			cellHeight: soundBlockSize+2*spacing

		}

	}
}
