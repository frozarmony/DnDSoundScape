#ifndef MUSICSOUNDMODEL_H
#define MUSICSOUNDMODEL_H

#include <QtCore/qmath.h>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "soundmodel.h"

class MusicSoundModel : public SoundModel
{
	Q_OBJECT
public:
	// Constructor
	MusicSoundModel(const QString& name, const QString& imgPath, bool random);

	// Method
	void				addMusic(const QString& musicPath);

protected:
	// Inherited Method
	bool				isPlayingSound();
	void				startSound();
	void				stopSound();

public slots:
	void				onMasterVolumeChanged();

private:
	QMediaPlayer		m_player;
	QMediaPlaylist		m_playList;
};

#endif // MUSICSOUNDMODEL_H
