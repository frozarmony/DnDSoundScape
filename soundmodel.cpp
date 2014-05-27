#include "soundmodel.h"

// Constants Type
const int	SoundModel::TYPE_ONE_SHOT;
const int	SoundModel::TYPE_AMBIANT;
const int	SoundModel::TYPE_MUSIC;
const int	SoundModel::TYPE_PLACE;

// Constructor
SoundModel::SoundModel(int type, const QString& name, const QString& imgPath, QObject *parent) :
	QObject(parent),
	m_type(type),
	m_name(name),
	m_imgPath(imgPath),
	m_masterVolume(1)
{
}

// Getter
int		SoundModel::type() const{			return m_type;			}
QString SoundModel::name() const{			return m_name;			}
QString SoundModel::imgPath() const{		return m_imgPath;		}
double	SoundModel::masterVolume() const{	return m_masterVolume;	}

// Setter
void	SoundModel::setMasterVolume(double masterVolume){
	if(m_masterVolume != masterVolume){
		m_masterVolume = masterVolume;
		emit masterVolumeChanged();
	}
}

// Method
bool SoundModel::isPlaying(){
	return isPlayingSound();
}

void SoundModel::start(){
	startSound();
}

void SoundModel::stop(){
	stopSound();
}
