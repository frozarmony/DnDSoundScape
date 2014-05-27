#include "mastervolumemodel.h"


// Constructor
MasterVolumeModel::MasterVolumeModel(QObject *parent) : QObject(parent), m_volume(1.0) {}

// Getter
double MasterVolumeModel::volume() const{ return m_volume; }

// Setter
void MasterVolumeModel::setVolume(double newVolume){ if(m_volume!=newVolume){m_volume = newVolume; emit volumeChanged(m_volume);} }
