#include "placesoundmodel.h"

// Constructor
PlaceSoundModel::PlaceSoundModel(const QString& name, const QString& imgPath) :
	SoundModel(SoundModel::TYPE_PLACE, name, imgPath),
	m_playingChildrenSounds(0)
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
