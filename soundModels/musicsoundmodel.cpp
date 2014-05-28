#include "musicsoundmodel.h"

// Constructor
MusicSoundModel::MusicSoundModel(const QString &name, const QString &imgPath, bool random) :
	SoundModel(SoundModel::TYPE_MUSIC, name, imgPath),
	m_player(),
	m_playList()
{
	// Config Playlist
	m_playList.setPlaybackMode((random)?QMediaPlaylist::Random:QMediaPlaylist::Loop);
	m_player.setPlaylist(&m_playList);

	// MasterVolumeChanged handling
	QObject::connect(this, SIGNAL(masterVolumeChanged()),
					 this, SLOT(onMasterVolumeChanged()));
}

// Method
void MusicSoundModel::addMusic(const QString &musicPath){
	m_playList.addMedia(QUrl(musicPath));
}

// IsPlaying, Start & Stop
bool MusicSoundModel::isPlayingSound(){
	return m_player.state() == QMediaPlayer::PlayingState;
}

void MusicSoundModel::startSound(){
	if(!isPlaying()){
		// If Random, play next
		if( m_playList.playbackMode() == QMediaPlaylist::Random )
			m_playList.next();

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
