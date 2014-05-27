#include "musicsoundmodel.h"

MusicSoundModel::MusicSoundModel(const QString &name, const QString &imgPath, const QString &soundPath) :
	SoundModel(SoundModel::TYPE_MUSIC, name, imgPath),
	m_player()
{
	// Load Sound
	m_player.setMedia(QUrl::fromLocalFile(soundPath));

	// MasterVolumeChanged handling
	QObject::connect(this, SIGNAL(masterVolumeChanged()),
					 this, SLOT(onMasterVolumeChanged()));
}

// IsPlaying, Start & Stop
bool MusicSoundModel::isPlayingSound(){
	return m_player.state() == QMediaPlayer::PlayingState;
}

void MusicSoundModel::startSound(){
	if(!isPlaying()){
		// Play it
		qDebug() << "Start";
		m_player.setVolume(qFloor(masterVolume()*100.0));
		m_player.play();
		emit started();
	}
}

void MusicSoundModel::stopSound(){
	if(isPlaying()){
		// Play it
		m_player.stop();
		emit stopped();
	}
}

void MusicSoundModel::onMasterVolumeChanged(){
	if(isPlaying())
		m_player.setVolume(qFloor(masterVolume()*100.0));
}
