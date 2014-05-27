#ifndef ONESHOTSOUNDMODEL_H
#define ONESHOTSOUNDMODEL_H

#include <qglobal.h>
#include <QtCore/qmath.h>
#include <QVector>
#include <QMediaPlayer>

#include "soundmodel.h"

class OneShotSoundModel : public SoundModel
{
public:
	// Contructor
	OneShotSoundModel(const QString& name, const QString& imgPath);

	// Method
	void						addSound( const QString& soundPath );

protected:
	// inherited Method
	bool						isPlayingSound();
	void						startSound();
	void						stopSound();

private:
	QVector<QMediaPlayer*>		m_sounds;
};

#endif // ONESHOTSOUNDMODEL_H
