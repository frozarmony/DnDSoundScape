#include "backend.h"

// Constructor
Backend::Backend(QQmlContext *ctxt, QObject *parent) :
	QObject(parent),

	// Base Member
	m_soundDB(),
	m_ctxt(ctxt),
	m_mainPlayingSound(NULL),
	m_loadedPlace(NULL),

	// Masters Volume
	m_generalMaster(),
	m_oneShotMaster(),
	m_ambiantMaster(),
	m_musicMaster(),

	// Places Models
	m_placesPanel("Places", 1),
	m_atmospheresPanel("Atmospheres", 2),
	m_miscellaneousPanel("Miscellaneous", 2),

	// Panels Models
	m_placesPanels(),
	m_universalPanels()
{
	// Constant
	ctxt->setContextProperty("TYPE_ONE_SHOT", QVariant::fromValue(SoundModel::TYPE_ONE_SHOT));
	ctxt->setContextProperty("TYPE_AMBIANT", QVariant::fromValue(SoundModel::TYPE_AMBIANT));
	ctxt->setContextProperty("TYPE_MUSIC", QVariant::fromValue(SoundModel::TYPE_MUSIC));
	ctxt->setContextProperty("TYPE_PLACE", QVariant::fromValue(SoundModel::TYPE_PLACE));

	// Backend
	ctxt->setContextProperty("backend", QVariant::fromValue(this));

	// Masters
	initMastersVolume();

	// Panels
	initPlacesPanels();
	m_ctxt->setContextProperty("universalPanelsList", QVariant::fromValue((QList<QObject*>&)m_universalPanels));
}

// Qml Interface
void Backend::test(){
	qDebug() << "Test lauched";
	loadXmlFile("dndData/dnd.xml");
}

// Destructor
Backend::~Backend(){
	//for(QList<SoundModel*>::Iterator it = m_soundDB.begin(); it!=m_soundDB.end(); ++it)
		//delete (*it);
}

// Private Slots
void Backend::onSoundStart(){
	SoundModel* sound = (SoundModel*)QObject::sender();

	if( sound->type() == SoundModel::TYPE_PLACE || sound->type() == SoundModel::TYPE_MUSIC ){
		if( m_mainPlayingSound != NULL ){
			m_mainPlayingSound->stop();
		}
		m_mainPlayingSound = sound;
		qDebug() << "MainSoundChanged : " << sound->name();
	}
}

void Backend::onSoundStop(){
	SoundModel* sound = (SoundModel*)QObject::sender();

	if( sound->type() == SoundModel::TYPE_PLACE || sound->type() == SoundModel::TYPE_MUSIC ){
		if( m_mainPlayingSound == sound ){
			m_mainPlayingSound = NULL;
			qDebug() << "MainSoundChanged : NULL";
		}
	}
}

// Tool Method
void Backend::initMastersVolume(){
	// Make links
	//QObject::connect(&m_generalMaster, SIGNAL(volumeChanged(double)), &m_oneShotMaster, SLOT(setVolume(double)));

	// Load in QML Context
	m_ctxt->setContextProperty("generalMaster", QVariant::fromValue(&m_generalMaster));
	m_ctxt->setContextProperty("oneshotMaster", QVariant::fromValue(&m_oneShotMaster));
	m_ctxt->setContextProperty("ambiantMaster", QVariant::fromValue(&m_ambiantMaster));
	m_ctxt->setContextProperty("musicMaster", QVariant::fromValue(&m_musicMaster));
}

void Backend::initPlacesPanels(){
	// Make Places Panels List
	m_placesPanels.append(&m_placesPanel);
	m_placesPanels.append(&m_atmospheresPanel);
	m_placesPanels.append(&m_miscellaneousPanel);

	// Update Context
	m_ctxt->setContextProperty("placesPanelsList", QVariant::fromValue((QList<QObject*>&)m_placesPanels));
}

SoundModel * Backend::registerSound(SoundModel *sound, bool subSound = false){
	m_soundDB.append(sound);

	if(!subSound){
		// On Sound Started & Stopped
		QObject::connect(sound, SIGNAL(started()), this, SLOT(onSoundStart()));
		QObject::connect(sound, SIGNAL(stopped()), this, SLOT(onSoundStop()));
	}

	switch (sound->type()) {
	case SoundModel::TYPE_ONE_SHOT:
		QObject::connect(&m_oneShotMaster, SIGNAL(volumeChanged(double)), sound, SLOT(setMasterVolume(double)));
		break;
	case SoundModel::TYPE_AMBIANT:
		QObject::connect(&m_ambiantMaster, SIGNAL(volumeChanged(double)), sound, SLOT(setMasterVolume(double)));
		break;
	case SoundModel::TYPE_MUSIC:
		QObject::connect(&m_musicMaster, SIGNAL(volumeChanged(double)), sound, SLOT(setMasterVolume(double)));
		break;
	case SoundModel::TYPE_PLACE:
		/* Do Nothing */
		break;
	default:
		qDebug() << "RegisterSound : Unknown sound type !!";
		break;
	}

	return sound;
}

void Backend::loadPlace(PlaceSoundModel *place){
	if( m_loadedPlace != place && place != NULL ){
		// Clear Old Place
		m_atmospheresPanel.clear();
		m_miscellaneousPanel.clear();

		// Load place
		foreach (SoundModel* sound, place->sounds()) {
			if(sound->type() <= SoundModel::TYPE_MUSIC)
				m_miscellaneousPanel.addSound(sound);
			else
				m_atmospheresPanel.addSound(sound);
		}
		m_loadedPlace = place;
	}
}

void Backend::loadXmlFile(const QString &filePath){
	// Open File
	QDomDocument doc("dnd");
	QFile file(filePath);
	QString errorMsg;
	int line, col;

	if (!file.open(QIODevice::ReadOnly)){
		qDebug() << "File does not exist.";
		return;
	}

	if (!doc.setContent(file.readAll(), &errorMsg, &line, &col)) {
		file.close();
		qDebug() << "Xml Parse failed.";
		qDebug() << "Error : " << errorMsg << "," << line << "," << col;
		return;
	}
	file.close();

	// Get AbsolutePath
	QFileInfo info(file);
	QString dataPath = info.absolutePath();

	QDomElement docElem = doc.documentElement();
	QDomNode node;

	// Universal
	QDomElement universal = docElem.elementsByTagName("universal").at(0).toElement();
	QDomNodeList categories = universal.elementsByTagName("category");
	for(int i=0; i<categories.count(); ++i){	// Foreach Category
		node = categories.at(i);

		if( node.isElement() ){
			// Add New Category
			QDomElement category = node.toElement();
			PanelModel* categoryPanel = new PanelModel(category.attribute("name", "Undefined Category"),
													   category.attribute("rowWidth", "2").toInt());

			// Fill Category
			QDomNodeList sounds = category.childNodes();
			for(int j=0; j<sounds.count(); ++j){	// Foreach Sound in Category
				node = sounds.at(j);

				if( node.isElement() ){
					categoryPanel->addSound( loadSound(node.toElement(), dataPath) );
				}
			}

			m_universalPanels.append(categoryPanel);
		}
	}

	// Places
	QDomElement places = docElem.elementsByTagName("places").at(0).toElement();
	QDomNodeList placesList = places.elementsByTagName("place");
	for(int i=0; i<placesList.count(); ++i){	// Foreach Place
		node = placesList.at(i);

		if( node.isElement() ){
			qDebug() << "Adding Place";
			// Add New Place
			QDomElement place = node.toElement();
			PlaceSoundModel* placeModel = new PlaceSoundModel(
						place.attribute("name"),
						dataPath + "/" + place.attribute("imgPath")
			);

			// Fill Place
			QDomNodeList sounds = place.childNodes();
			for(int j=0; j<sounds.count(); ++j){	// Foreach Sound in Place
				node = sounds.at(j);

				if( node.isElement() ){
					placeModel->addSound( loadSound(node.toElement(), dataPath) );
				}
			}

			registerSound(placeModel);
			m_placesPanel.addSound(placeModel);
		}
	}

	// Update Model in QML
	m_ctxt->setContextProperty("universalPanelsList", QVariant::fromValue((QList<QObject*>&)m_universalPanels));

	// Reset Masters
	m_generalMaster.setVolume(0.8);
	m_oneShotMaster.setVolume(0.8);
	m_ambiantMaster.setVolume(0.8);
	m_musicMaster.setVolume(0.8);
}

SoundModel* Backend::loadSound(const QDomElement &xmlSound, const QString &dataPath){
	QString tagName = xmlSound.tagName();

	if( tagName == "oneshot" ){
		OneShotSoundModel* sound = new OneShotSoundModel(
					xmlSound.attribute("name"),
					dataPath + "/" + xmlSound.attribute("imgPath")
		);

		// Get Each sub-sounds
		QDomNodeList subSounds = xmlSound.elementsByTagName("soundfile");
		for(int i=0; i<subSounds.count(); ++i)
			sound->addSound( dataPath + "/" + subSounds.at(i).toElement().attribute("path") );

		return registerSound(sound);
	}
	else if( tagName == "ambiant" ){
		AmbiantSoundModel* ambiant = new AmbiantSoundModel(
									xmlSound.attribute("name"),
									dataPath + "/" + xmlSound.attribute("imgPath"),
									dataPath + "/" + xmlSound.attribute("soundPath"),
									xmlSound.attribute("loopDuration", "10000").toInt(),
									xmlSound.attribute("shadingDuration", "500").toInt()
					);

		// Get Each sub-sounds
		QDomNodeList subSounds = xmlSound.elementsByTagName("oneshot");
		for(int i=0; i<subSounds.count(); ++i){
			// Get oneShot Node
			QDomElement xmlSubSound = subSounds.at(i).toElement();
			OneShotSoundModel* sound = new OneShotSoundModel(
						xmlSubSound.attribute("name"),
						dataPath + "/" + xmlSubSound.attribute("imgPath")
			);

			// Get Distribution params
			double mTime = xmlSubSound.attribute("mTime", "10000").toDouble();
			double sdTime = xmlSubSound.attribute("sdTime", "1000").toDouble();

			// Get Each sub-sounds of oneshot
			QDomNodeList subSubSounds = xmlSubSound.elementsByTagName("soundfile");
			for(int i=0; i<subSubSounds.count(); ++i)
				sound->addSound( dataPath + "/" + subSubSounds.at(i).toElement().attribute("path") );

			registerSound(sound);
			ambiant->addRandomOneShot(*sound, mTime, sdTime);
		}

		// Register Ambiant
		return registerSound(ambiant);
	}
	else if( tagName == "music" ){
		return registerSound(new MusicSoundModel(
						  xmlSound.attribute("name"),
						  dataPath + "/" + xmlSound.attribute("imgPath"),
						  dataPath + "/" + xmlSound.attribute("soundPath")
		));
	}
	else
		qDebug() << "The sound type '" << tagName << "' does not exist.";

	return NULL;
}
