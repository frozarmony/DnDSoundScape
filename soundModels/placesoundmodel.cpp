#include "placesoundmodel.h"

// Constructor
PlaceSoundModel::PlaceSoundModel(const QString& name, const QString& imgPath) :
	SoundModel(SoundModel::TYPE_PLACE, name, imgPath),
	m_playingChildrenSounds(0),
	m_mainSound(NULL)
{
}

// Getter
const QList<PanelModel*> PlaceSoundModel::categories() const{
	return m_categories;
}

// Method
void PlaceSoundModel::addCategory(PanelModel* newCategory){
	// Connect Child Sounds
	for( int i=0; i<newCategory->rowCount(); ++i){
		SoundModel* newSound = newCategory->getSound(i);
		QObject::connect(newSound, SIGNAL(started()), this, SLOT(onChildSoundStarted()));
		QObject::connect(newSound, SIGNAL(stopped()), this, SLOT(onChildSoundStopped()));
	}

	// Add Category
	m_categories.append(newCategory);
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
		foreach (PanelModel* panel, m_categories) {
			for( int i=0; i<panel->rowCount(); ++i){
				SoundModel* sound = panel->getSound(i);
				if(sound->isPlaying()){
					sound->stop();
				}
			}
		}
	}
}

// Private Slots
void PlaceSoundModel::onChildSoundStarted(){
	SoundModel* senderSound = ((SoundModel*)QObject::sender());
	if( senderSound->type() != SoundModel::TYPE_ONE_SHOT ){
		int oldPlayingChildrenSounds = m_playingChildrenSounds;

		++m_playingChildrenSounds;
		qDebug() << "Place : Sound Started : " << senderSound->name() << " (" << m_playingChildrenSounds << ")";

		if( senderSound->type() == SoundModel::TYPE_MUSIC ){
			if( m_mainSound != NULL )
				m_mainSound->stop();

			m_mainSound = senderSound;
		}

		// Check for started signal
		if(oldPlayingChildrenSounds == 0){
			emit started();
		}
	}
}

void PlaceSoundModel::onChildSoundStopped(){
	SoundModel* senderSound = ((SoundModel*)QObject::sender());
	if( senderSound->type() != SoundModel::TYPE_ONE_SHOT ){
		--m_playingChildrenSounds;
		qDebug() << "Place : Sound Stopped : " << senderSound->name() << " (" << m_playingChildrenSounds << ")";

		if( senderSound == m_mainSound ){
			m_mainSound = NULL;
		}

		// Check for stopped signal
		if(m_playingChildrenSounds < 1){
			emit stopped();
		}
	}
}
