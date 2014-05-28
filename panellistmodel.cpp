#include "PanelListModel.h"

// Constructor
PanelListModel::PanelListModel(QObject *parent) :
	QAbstractListModel(parent),
	m_panels()
{
}

// Method
void PanelListModel::addPanel(PanelModel *panel){
	beginInsertRows(QModelIndex(), rowCount(), rowCount());
	m_panels << panel;
	endInsertRows();
}

void PanelListModel::removePanel(int index){
	beginRemoveRows(QModelIndex(), index, index);
	m_panels.removeAt(index);
	endRemoveRows();
}

// QAbstractListModel Implementation
QHash<int, QByteArray> PanelListModel::roleNames() const{
	QHash<int, QByteArray> roles;
	roles[Qt::UserRole+1] = "panel";
	return roles;
}

int PanelListModel::rowCount(const QModelIndex& ) const
{
	return m_panels.size();
}

QVariant PanelListModel::data(const QModelIndex &index, int role) const
{
	if(index.row() < 0 || index.row() > m_panels.count())
		return QVariant();

	if(role == Qt::UserRole+1)
		return QVariant::fromValue((QObject*)m_panels[index.row()]);

	return QVariant();
}
