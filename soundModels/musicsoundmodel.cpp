#include "musicsoundmodel.h"

// Constructor
MusicSoundModel::MusicSoundModel(const QString &name, const QString &imgPath, const QString& mode) :
	SoundModel(SoundModel::TYPE_MUSIC, name, imgPath),
	m_player(),
	m_playList()
{
	// Config Playlist
	if( mode == "random" )
		m_playList.setPlaybackMode(QMediaPlaylist::Random);
	else if( mode == "random" )
		m_playList.setPlaybackMode(QMediaPlaylist::Loop);
	else
		m_playList.setPlaybackMode(QMediaPlaylist::Sequential);
	m_player.setPlaylist(&m_playList);

	// OnMusicStop
	QObject::connect(&m_player, SIGNAL(stateChanged(QMediaPlayer::State)),
					 this, SLOT(onPlayerStop(QMediaPlayer::State)));

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
		// Stop it
		m_player.stop();
		emit stopped();
	}
}

void MusicSoundModel::onMasterVolumeChanged(){
	if(isPlaying())
		m_player.setVolume(qFloor(masterVolume()*100.0));
}

void MusicSoundModel::onPlayerStop(QMediaPlayer::State state){
	if( state == QMediaPlayer::StoppedState )
		emit stopped();
}
