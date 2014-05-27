#ifndef MUSICSOUNDMODEL_H
#define MUSICSOUNDMODEL_H

#include <QtCore/qmath.h>
#include <QMediaPlayer>

#include "soundmodel.h"

class MusicSoundModel : public SoundModel
{
	Q_OBJECT
public:
	// Constructor
	MusicSoundModel(const QString& name, const QString& imgPath, const QString& soundPath);

protected:
	// Inherited Method
	bool				isPlayingSound();
	void				startSound();
	void				stopSound();

public slots:
	void				onMasterVolumeChanged();

private:
	QMediaPlayer		m_player;
};

#endif // MUSICSOUNDMODEL_H
