#ifndef DumpModel_H
#define DumpModel_H

#include <QAbstractTableModel>
#include <QItemDelegate>
#include "ipacket.h"

struct Item {
	IPacket*packet;
	bool forward;
	bool valid;
};

//! model-class
class DumpModel : public QAbstractTableModel
{
public:
    DumpModel();
    virtual int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    virtual int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
    virtual QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
     void add (bool forward, IPacket*packet);
private:
    int rows;
    int columns;
    QList<Item> packets;
};
#endif // CmdFieldsModel_H
