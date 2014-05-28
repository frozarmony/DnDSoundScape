#ifndef PANELLISTMODEL_H
#define PANELLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include "panelmodel.h"

class PanelListModel : public QAbstractListModel
{
	Q_OBJECT

public:
	// Constructor
	explicit PanelListModel(QObject *parent = 0);

	// Method
	void					addPanel(PanelModel* panel);
	void					removePanel(int index);

	// QAbstractListModel Implementation
	QHash<int, QByteArray>	roleNames() const;
	int						rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant				data(const QModelIndex &index, int role) const;

private:
	// Member
	QList<PanelModel*>		m_panels;
};

#endif // PANELLISTMODEL_H
