#include "placesoundmodel.h"

// Constructor
PlaceSoundModel::PlaceSoundModel(const QString& name, const QString& imgPath) :
	SoundModel(SoundModel::TYPE_PLACE, name, imgPath),
	m_playingChildrenSounds(0)
{
}

// Getter
const QList<SoundModel*> PlaceSoundModel::sounds() const{
	return m_sounds;
}

// Method
void PlaceSoundModel::addSound(SoundModel* newSound){
	QObject::connect(newSound, SIGNAL(started()), this, SLOT(onChildSoundStarted()));
	QObject::connect(newSound, SIGNAL(stopped()), this, SLOT(onChildSoundStopped()));
	m_sounds.append(newSound);
}

// IsPlaying, Start & Stop
bool PlaceSoundModel::isPlayingSound(){
	return m_playingChildrenSounds > 0;
}

void PlaceSoundModel::startSound(){
	/* Do Nothing */
}

void PlaceSoundModel::stopSound(){
	if( isPlayingSound() ){
		foreach (SoundModel* sound, m_sounds) {
			if(sound->isPlaying()){
				sound->stop();
			}
		}
	}
}

// Private Slots
void PlaceSoundModel::onChildSoundStarted(){
	if( ((SoundModel*)QObject::sender())->type() != SoundModel::TYPE_ONE_SHOT ){
		++m_playingChildrenSounds;

		// Check for started signal
		if(m_playingChildrenSounds == 1){
			emit started();
		}
	}
}

void PlaceSoundModel::onChildSoundStopped(){
	if( ((SoundModel*)QObject::sender())->type() != SoundModel::TYPE_ONE_SHOT ){
		--m_playingChildrenSounds;

		// Check for stopped signal
		if(m_playingChildrenSounds < 1){
			emit stopped();
		}
	}
}
