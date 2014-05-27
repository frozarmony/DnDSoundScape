#ifndef AMBIANTSOUNDMODEL_H
#define AMBIANTSOUNDMODEL_H

#include <iostream>
#include <random>

#include <qglobal.h>
#include <QtCore/qmath.h>
#include <QMap>
#include <QMediaPlayer>
#include <QPropertyAnimation>
#include <QTimer>

#include "soundmodel.h"
#include "oneshotsoundmodel.h"

class AmbiantSoundModel : public SoundModel
{
	Q_OBJECT
public:
	// Constructor
	AmbiantSoundModel(const QString& name, const QString& imgPath, const QString& soundPath, int loopDuration = 10000, int shadingDuration = 1000);

	// Method
	void									addRandomOneShot(OneShotSoundModel& sound, double mTime, double sdTime);

protected:
	// Inherited Method
	bool									isPlayingSound();
	void									startSound();
	void									stopSound();

public slots:
	void									loop();
	void									stopAfterShading(QAbstractAnimation::State newState);
	void									onMasterVolumeChanged();

private slots:
	void									onRandomTimerTimeout();

private:
	// Ambiant Member
	QMediaPlayer							m_player;
	QTimer									m_loopTimer;
	QPropertyAnimation						m_shadeAnimation;

	// Random OneShot Struct
	struct RandomOneShotSoundModel{
		OneShotSoundModel*					sound;
		std::normal_distribution<double>	distribution;
	};

	// Random OneShot Member
	QMap<QTimer*, RandomOneShotSoundModel>	m_randomOneShots;
	std::default_random_engine				m_generator;

	// Random OneShot Method
	void									startRandomTimer(QTimer& timer, RandomOneShotSoundModel& model);
	void									stopRandomTimers();
};

#endif // AMBIANTSOUNDMODEL_H
