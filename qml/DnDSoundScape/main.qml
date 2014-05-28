import QtQuick 2.0

Rectangle {
	id: mainWindow

	// Property
    property int soundBlockSize:  100

    width: 1000
    height: 400

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
                spacing: 30

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
        id: universalPanelsListView

        model: universalPanelsList
		delegate: SoundPanel {
            panelModel: panel
			width: parent.width
			soundBlockSize: soundBlockSize
		}

        width: mainWindow.width/2
		anchors.bottom: controllerView.top
		anchors.left: parent.left
		anchors.top: parent.top
        anchors.right: placesPanelsListView.left
		anchors.margins: 10
		clip: true
		spacing: 10

        Image {
          height: 15
          anchors.right: parent.right
          anchors.rightMargin: 0
          anchors.left: parent.left
          anchors.leftMargin: 0
          anchors.top: parent.top
          anchors.topMargin: 0
          source: "img/shadow-border.png"
        }

        Image {
          y: 30
          height: 15
          anchors.right: parent.right
          anchors.rightMargin: 0
          anchors.left: parent.left
          anchors.leftMargin: 0
          anchors.bottom: parent.bottom
          anchors.bottomMargin: 0
          rotation: 180
          source: "img/shadow-border.png"
        }
	}

	// Universale Part
    ListView {
        id: placesPanelsListView

        model: placesPanelsList
		delegate: SoundPanel {
            panelModel: panel
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
        opacity: (placesPanelsListView.count===0)?0:1

        Image {
          height: 15
          anchors.right: parent.right
          anchors.rightMargin: 0
          anchors.left: parent.left
          anchors.leftMargin: 0
          anchors.top: parent.top
          anchors.topMargin: 0
          source: "img/shadow-border.png"
        }

        Image {
          y: 30
          height: 15
          anchors.right: parent.right
          anchors.rightMargin: 0
          anchors.left: parent.left
          anchors.leftMargin: 0
          anchors.bottom: parent.bottom
          anchors.bottomMargin: 0
          rotation: 180
          source: "img/shadow-border.png"
        }

		// View Animation
		Behavior on opacity { PropertyAnimation{ duration: 1000 } }
	}

}
