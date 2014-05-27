#ifndef SOUNDMODEL_H
#define SOUNDMODEL_H

#include <QDebug>
#include <QObject>
#include <QStandardItem>
#include <QMediaPlayer>

class SoundModel : public QObject
{
	Q_OBJECT

	Q_PROPERTY(int type READ type NOTIFY typeChanged)
	Q_PROPERTY(QString name READ name NOTIFY nameChanged)
	Q_PROPERTY(QString imgPath READ imgPath NOTIFY imgPathChanged)
	Q_PROPERTY(double masterVolume READ masterVolume WRITE setMasterVolume NOTIFY masterVolumeChanged)

public:
	// Constants Type
	static const int	TYPE_ONE_SHOT	= 0;
	static const int	TYPE_AMBIANT	= 1;
	static const int	TYPE_MUSIC		= 2;
	static const int	TYPE_PLACE		= 3;

	// Constructor
	explicit SoundModel(int type, const QString& name, const QString& imgPath, QObject *parent = 0);

	// Getter
	int					type() const;
	QString				name() const;
	QString				imgPath() const;
	double				masterVolume() const;

	// Method
	Q_INVOKABLE bool	isPlaying();
	Q_INVOKABLE void	start();
	Q_INVOKABLE void	stop();

public slots:
	// Setter
	void				setMasterVolume(double masterVolume);

signals:
	// Property Signals
	void				typeChanged();
	void				nameChanged();
	void				imgPathChanged();
	void				masterVolumeChanged();

	// Method Signals
	void				started();
	void				stopped();

protected:
	virtual bool		isPlayingSound() = 0;
	virtual void		startSound() = 0;
	virtual void		stopSound() = 0;

private:
	// Property
	int					m_type;
	QString				m_name;
	QString				m_imgPath;
	double				m_masterVolume;
};

#endif // SOUNDMODEL_H
