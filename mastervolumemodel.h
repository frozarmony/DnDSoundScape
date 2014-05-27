#ifndef MASTERVOLUMEMODEL_H
#define MASTERVOLUMEMODEL_H

#include <QDebug>
#include <QObject>

class MasterVolumeModel : public QObject{
	Q_OBJECT

	Q_PROPERTY(double volume READ volume WRITE setVolume NOTIFY volumeChanged)

public:
	// Constructor
	MasterVolumeModel(QObject* parent = 0);

	// Getter
	double		volume() const;

public slots:
	// Setter
	void		setVolume(double newVolume);

signals:
	void		volumeChanged(double newVolume);

private:
	double		m_volume;
};

#endif // MASTERVOLUMEMODEL_H
