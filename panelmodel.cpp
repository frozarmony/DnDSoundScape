#include "PanelModel.h"

// Constructor
PanelModel::PanelModel(const QString& name, int rowWidth, QObject *parent) :
	QAbstractListModel(parent),
	m_name(name),
	m_rowWidth(rowWidth),
	m_sounds()
{
}

// Getter
QString						PanelModel::name() const{			return m_name;			}
int							PanelModel::rowWidth() const{		return m_rowWidth;		}

// Method
void PanelModel::addSound(SoundModel *sound){
	beginInsertRows(QModelIndex(), rowCount(), rowCount());
	m_sounds << sound;
	endInsertRows();
}

SoundModel* PanelModel::getSound(int index){
	return m_sounds.at(index);
}

void PanelModel::clear(){
	beginRemoveRows(QModelIndex(), 0, rowCount());
	m_sounds.clear();
	endRemoveRows();
}

// QAbstractListModel Implementation
QHash<int, QByteArray> PanelModel::roleNames() const{
	QHash<int, QByteArray> roles;
	roles[Qt::UserRole+1] = "sound";
	return roles;
}

int PanelModel::rowCount(const QModelIndex& ) const
{
	return m_sounds.size();
}

QVariant PanelModel::data(const QModelIndex &index, int role) const
{
	if(index.row() < 0 || index.row() > m_sounds.count())
		return QVariant();

	if(role == Qt::UserRole+1)
		return QVariant::fromValue((QObject*)m_sounds[index.row()]);

	return QVariant();
}
