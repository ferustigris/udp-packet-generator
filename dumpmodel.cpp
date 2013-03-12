#include "dumpmodel.h"
#include "QStringList"
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QApplication>
#include "errors.h"


/*!\func
 *
 * \param no
 * \return no
 */
DumpModel::DumpModel()
{
	Log::add(Log::LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    rows = 0;
    columns = 1;
}
/*!\func
 *
 * \param no
 * \return no
 */
int DumpModel::rowCount ( const QModelIndex & ) const
{
    Log::add(Log::LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    return rows;
}
/*!\func
 *
 * \param no
 * \return no
 */
int DumpModel::columnCount ( const QModelIndex &) const
{
   Log::add(Log::LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    return columns;
}
/*!\func
 *
 * \param no
 * \return no
 */
QVariant DumpModel::data ( const QModelIndex &index, int role) const
{
    Log::add(Log::LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    if (!index.isValid())
	 return QVariant();
    if (role != Qt::DisplayRole && role != Qt::EditRole)
	 return QVariant();
	    return QString(packets[index.row()].forward ? "->" : "<-") + "   "+ packets[index.row()].packet->toText();
}
/*!\func
 *
 * \param no
 * \return no
 */
void DumpModel::add (bool forward,  IPacket*packet)
{
    Log::add(Log::LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    beginInsertRows(QModelIndex (),0,0);
    Item item;
    item.forward = forward;
    item.packet = packet;
    packets.append(item);
    rows++;
    endInsertRows();
}
/*!\func
 *
 * \param no
 * \return no
 */
Qt::ItemFlags DumpModel::flags(const QModelIndex &index) const
{
    Log::add(Log::LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
     if (!index.isValid())
	 return 0;
     return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
/*!\func
 *
 * \param no
 * \return no
 */
QVariant DumpModel::headerData ( int section, Qt::Orientation orientation, int role) const
{
    Log::add(Log::LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    if (role != Qt::DisplayRole)
	 return QVariant();
    if (orientation == Qt::Vertical)
	 return QVariant();
    return qApp->translate("MainWindow", "Packet");
}
