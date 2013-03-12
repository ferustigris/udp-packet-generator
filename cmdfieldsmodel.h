#ifndef CmdFieldsModel_H
#define CmdFieldsModel_H

#include <QAbstractTableModel>
#include <QItemDelegate>
#include "block.h"

//! model-class
class CmdFieldsModel : public QAbstractTableModel
{
public:
    CmdFieldsModel(const QString&data = "");
    virtual int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    virtual int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
    virtual QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    bool insertRow ( int row, const QModelIndex & parent = QModelIndex() );
    bool removeRow ( int row, const QModelIndex & parent = QModelIndex() );
    virtual bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
    Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    const QList<Block>& getList();
private:
    int rows;
    int columns;
    QList<Block> inputs;
signals:
    void changed ();
};
class CmdFieldsDelegate : public QItemDelegate
{
public:
    CmdFieldsDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // CmdFieldsModel_H
