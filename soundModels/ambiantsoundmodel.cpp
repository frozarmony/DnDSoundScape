#include "ambiantsoundmodel.h"

// Constructor
AmbiantSoundModel::AmbiantSoundModel(const QString &name, const QString &imgPath, const QString &soundPath, int loopDuration, int shadingDuration) :
	SoundModel(SoundModel::TYPE_AMBIANT, name, imgPath),
	m_player(0, QMediaPlayer::LowLatency),
	m_loopTimer(),
	m_shadeAnimation(&m_player, "volume"),
	m_generator()
{
	// Load Sound
	QUrl url = QUrl::fromLocalFile(soundPath);
	m_player.setMedia(url);

	// Loop Handling
	m_loopTimer.setInterval(loopDuration);
	QObject::connect(&m_loopTimer, SIGNAL(timeout()), this, SLOT(loop()));

	// Setup shade animation
	QObject::connect(&m_shadeAnimation, SIGNAL(stateChanged(QAbstractAnimation::State,QAbstractAnimation::State)),
					 this, SLOT(stopAfterShading(QAbstractAnimation::State)));
	m_shadeAnimation.setDuration(shadingDuration);

	// MasterVolumeChanged handling
	QObject::connect(this, SIGNAL(masterVolumeChanged()),
					 this, SLOT(onMasterVolumeChanged()));
}

// Method
void AmbiantSoundModel::addRandomOneShot(OneShotSoundModel& sound, double mTime, double sdTime){
	// Create Random Struct
	RandomOneShotSoundModel randSound;
	randSound.sound				= &sound;
	randSound.distribution		= std::normal_distribution<double>(mTime, sdTime);

	// Create and Connect QTimer
	QTimer* timer = new QTimer();
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(onRandomTimerTimeout()));

	// Add to map
	m_randomOneShots.insert(timer, randSound);
}

// IsPlaying, Start & Stop
bool AmbiantSoundModel::isPlayingSound(){
	return m_player.state() == QMediaPlayer::PlayingState;
}

void AmbiantSoundModel::startSound(){
	if(!isPlaying()){
		// Begin of sound
		m_player.setPosition(0);

		// Setup shade animation
		m_shadeAnimation.setStartValue(QVariant::fromValue(0));
		m_shadeAnimation.setEndValue(QVariant::fromValue(qFloor(masterVolume()*100.0)));

		// Start Random OneShot Sounds
		for(QMap<QTimer*, RandomOneShotSoundModel>::Iterator it = m_randomOneShots.begin(); it != m_randomOneShots.end(); ++it)
			startRandomTimer(*(it.key()), it.value() );

		// Play it and Start Periodic Timer
		m_player.play();
		m_loopTimer.start();
		m_shadeAnimation.start();
		emit started();
	}
}

void AmbiantSoundModel::stopSound(){
	if(isPlaying()){
		// Setup shade animation
		m_shadeAnimation.setStartValue(QVariant::fromValue(m_player.volume()));
		m_shadeAnimation.setEndValue(QVariant::fromValue(0));

		// Start Fade Out Animation and Stop Random OneShots
		m_shadeAnimation.start();
		stopRandomTimers();
		emit stopped();
	}
}

// Slots
void AmbiantSoundModel::loop(){
	m_player.setPosition(0);
}

// Stop Player after shading
void AmbiantSoundModel::stopAfterShading(QAbstractAnimation::State newState){
	if(newState == QAbstractAnimation::Stopped && m_player.volume() == 0){
		m_loopTimer.stop();
		m_player.stop();
	}
}

void AmbiantSoundModel::onMasterVolumeChanged(){
	// Update Main Loop Volume
	if(isPlaying()){
		if(m_shadeAnimation.state() == QAbstractAnimation::Stopped)
			m_player.setVolume(qFloor(masterVolume()*100.0));
		else if(m_shadeAnimation.startValue() == 0) // For Start Shading
			m_shadeAnimation.setEndValue(QVariant::fromValue(qFloor(masterVolume()*100.0)));
	}

	// Update Sub OneShots Volume
	for(QMap<QTimer*, RandomOneShotSoundModel>::Iterator it = m_randomOneShots.begin(); it != m_randomOneShots.end(); ++it)
		it.value().sound->setMasterVolume(masterVolume());
}

void AmbiantSoundModel::onRandomTimerTimeout(){
	// Get Source Timer
	QTimer* randTimer = (QTimer*)QObject::sender();

	// Get Corresponding OneShotSound
	QMap<QTimer*, RandomOneShotSoundModel>::Iterator it = m_randomOneShots.find(randTimer);

	if( it != m_randomOneShots.end() ){
		RandomOneShotSoundModel sound = (*it);
		sound.sound->start();
		startRandomTimer(*randTimer, sound);
	}
}

// Private Random One Shot Methods
void AmbiantSoundModel::startRandomTimer(QTimer &timer, RandomOneShotSoundModel &model){
	model.distribution.reset();
	double randTime = model.distribution(m_generator);

	timer.setSingleShot(true);
	timer.setInterval((int)qMax(10.0, randTime));
	timer.start();
}

void AmbiantSoundModel::stopRandomTimers(){
	QList<QTimer*> keys = m_randomOneShots.keys();
	for(QList<QTimer*>::Iterator it = keys.begin(); it != keys.end(); ++it)
		(*it)->stop();
}
