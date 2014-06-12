#ifndef BACKEND_H
#define BACKEND_H

#include <QDebug>
#include <QObject>
#include <QQmlContext>
#include <QMap>
#include <QSet>
#include <QFile>
#include <QFileInfo>
#include <QDomDocument>

#include "mastervolumemodel.h"
#include "panellistmodel.h"
#include "panelmodel.h"
#include "soundmodel.h"
#include "soundModels/placesoundmodel.h"
#include "soundModels/oneshotsoundmodel.h"
#include "soundModels/ambiantsoundmodel.h"
#include "soundModels/musicsoundmodel.h"

class Backend : public QObject
{
	Q_OBJECT

public:
	// Constructor
	explicit Backend(QQmlContext* context, QObject *parent = 0);

	// Qml Interface
	Q_INVOKABLE void test();
	Q_INVOKABLE void loadPlace(PlaceSoundModel* place);

	// Destructor
	~Backend();

private slots:
	void onSoundStart();
	void onSoundStop();

private:
	// Base Member
	QList<SoundModel*>			m_soundDB;
	QQmlContext*				m_ctxt;
	SoundModel*					m_mainPlayingSound;
	PlaceSoundModel*			m_loadedPlace;

	// Masters Volume
	//MasterVolumeModel			m_generalMaster;
	MasterVolumeModel			m_oneShotMaster;
	MasterVolumeModel			m_ambiantMaster;
	MasterVolumeModel			m_musicMaster;

	// Places Panels
	PanelModel					m_placesPanel;

	// Panels Models
	PanelListModel				m_placesPanels;
	PanelListModel				m_universalPanels;

	// Tool Method
	void						initMastersVolume();
	void						initPlacesPanels();
	SoundModel*					registerSound(SoundModel* sound, bool regSound);
	void						loadXmlFile(const QString& filePath);
	PanelModel*					loadCategory(const QDomElement& category, const QString& dataPath, bool regSound = true);
	SoundModel*					loadSound(const QDomElement& xmlSound, const QString& dataPath, bool regSound = true);

};

#endif // BACKEND_H
