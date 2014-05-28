#ifndef PANELMODEL_H
#define PANELMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include "soundmodel.h"

class PanelModel : public QAbstractListModel
{
	Q_OBJECT

	Q_PROPERTY(QString name READ name NOTIFY nameChanged)
	Q_PROPERTY(int rowWidth READ rowWidth NOTIFY rowWidthChanged)

public:
	// Constructor
	explicit PanelModel(const QString& name, int rowWidth, QObject *parent = 0);

	// Getter
	QString					name() const;
	int						rowWidth() const;

	// Method
	void					addSound(SoundModel* sound);
	SoundModel*				getSound(int index);
	void					clear();

	// QAbstractListModel Implementation
	QHash<int, QByteArray>	roleNames() const;
	int						rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant				data(const QModelIndex &index, int role) const;

signals:
	// Property Signals
	void					nameChanged();
	void					rowWidthChanged();

private:
	// Property
	QString					m_name;
	int						m_rowWidth;

	// Member
	QList<SoundModel*>		m_sounds;
};

#endif // PANELMODEL_H
