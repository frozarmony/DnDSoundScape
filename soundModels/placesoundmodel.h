#ifndef PLACESOUNDMODEL_H
#define PLACESOUNDMODEL_H

#include "panelmodel.h"

class PlaceSoundModel : public SoundModel
{
	Q_OBJECT
public:
	// Constructor
	PlaceSoundModel(const QString& name, const QString& imgPath);

	// Getter
	const QList<PanelModel*>	categories() const;

	// Method
	void						addCategory(PanelModel* newCategogy);

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
	QList<PanelModel*>			m_categories;
	int							m_playingChildrenSounds;
};

#endif // PLACESOUNDMODEL_H
