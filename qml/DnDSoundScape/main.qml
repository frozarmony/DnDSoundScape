import QtQuick 2.0

Rectangle {
	id: mainWindow

	// Property
    property int soundBlockSize:  100

	Image {
		id: background
		anchors.fill: parent
		source: "img/background-app.jpg"
	}

	Row {
		id: controllerView

		width: mainWindow.width/2
		height: 250
		anchors.bottom: parent.bottom
		anchors.left: parent.left
		anchors.leftMargin: 10
		spacing: 10

		Rectangle{

			height: parent.height
			width: 100
			color: "#00000000"

			Column{
				id: menuBar

				anchors.fill: parent

				Image {
					id: open
					width: 100
					height: 100
					source: "img/open-icon.png"

					MouseArea {
						id: openButton

						anchors.fill: parent

						onClicked: backend.test()
					}
				}

				Image {
					id: quit
					width: 100
					height: 100
					source: "img/quit-icon.png"

					MouseArea {
						id: quitButton

						anchors.fill: parent

						onClicked: Qt.quit()
					}
				}

			}

		}

		SoundController {
			name: "Master"
			masterVolumeModel: generalMaster
		}

		SoundController {
			name: "OneShot"
			masterVolumeModel: oneshotMaster
		}

		SoundController {
			name: "Ambiant"
			masterVolumeModel: ambiantMaster
		}

		SoundController {
			name: "Music"
			masterVolumeModel: musicMaster
		}

	}

	// Places Part
	ListView {
		id: placesPanelsListView

		model: placesPanelsList
		delegate: SoundPanel {
			panelModel: model.modelData
			width: parent.width
			soundBlockSize: soundBlockSize
		}

		width: mainWindow.width/2
		boundsBehavior: Flickable.StopAtBounds
		anchors.bottom: controllerView.top
		anchors.left: parent.left
		anchors.top: parent.top
		anchors.right: universalPanelsListView.left
		anchors.margins: 10
		clip: true
		spacing: 10
	}

	// Universale Part
	ListView {
		id: universalPanelsListView

		model: universalPanelsList
		delegate: SoundPanel {
			panelModel: model.modelData
			width: parent.width
			soundBlockSize: soundBlockSize
		}

		width: mainWindow.width/2
		anchors.top: parent.top
		anchors.bottom: parent.bottom
		anchors.right: parent.right
		anchors.margins: 10
		clip: true
		spacing: 10
		opacity: (universalPanelsListView.count===0)?0:1

		// View Animation
		Behavior on opacity { PropertyAnimation{ duration: 1000 } }
	}

}
