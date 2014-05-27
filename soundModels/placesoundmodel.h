#ifndef PLACESOUNDMODEL_H
#define PLACESOUNDMODEL_H

#include "soundmodel.h"

class PlaceSoundModel : public SoundModel
{
	Q_OBJECT
public:
	// Constructor
	PlaceSoundModel(const QString& name, const QString& imgPath);

	// Getter
	const QList<SoundModel*>	sounds() const;

	// Method
	void						addSound(SoundModel* newSound);

protected:
	// Inherited Method
	bool						isPlayingSound();
	void						startSound();
	void						stopSound();

private slots:
	void						onChildSoundStarted();
	void						onChildSoundStopped();

private:
	// Member
	QList<SoundModel*>			m_sounds;
	int							m_playingChildrenSounds;
};

#endif // PLACESOUNDMODEL_H
