#include "oneshotsoundmodel.h"

// Constructor
OneShotSoundModel::OneShotSoundModel(const QString &name, const QString &imgPath) :
	SoundModel(SoundModel::TYPE_ONE_SHOT, name, imgPath),
	m_sounds()
{
}

// Method
void OneShotSoundModel::addSound(const QString &soundPath){
	QMediaPlayer* newSound = new QMediaPlayer();
	newSound->setMedia(QUrl::fromLocalFile(soundPath));
	m_sounds.append(newSound);
}

// IsPlaying, Start & Stop
bool OneShotSoundModel::isPlayingSound(){
	return false;
}

void OneShotSoundModel::startSound(){
	if(m_sounds.count() > 0){
		// Choose Sound
		int index = qrand() % m_sounds.count();
		QMediaPlayer* selectedSound = m_sounds.at(index);

		// Play it
		selectedSound->setVolume(qFloor(this->masterVolume()*100.0));

		if( selectedSound->state() != QMediaPlayer::PlayingState )
			selectedSound->play();
		else
			selectedSound->setPosition(0);
		emit started();
	}
}

void OneShotSoundModel::stopSound(){
	/* Do Nothing */
}
