#include "cmdfieldsmodel.h"
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
CmdFieldsModel::CmdFieldsModel(const QString&data)
{
	Log::add(Log::LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    QStringList list = data.split("\n");
    rows = 0;
    foreach(QString line, list)
    {
	QStringList itemdata = line.split("\t");
	if(itemdata.count() < 4)continue;
	inputs.insert(rows + 1, Block(itemdata[0].toInt(),itemdata[1].toInt(),itemdata[2].toInt(),itemdata[3].toInt()));
	rows++;
    }
    columns = 5;
}
/*!\func
 *
 * \param no
 * \return no
 */
bool CmdFieldsModel::removeRow ( int row, const QModelIndex & parent)
{
	beginRemoveRows(parent, row, row);
	inputs.removeAt(row);
	endRemoveRows();
}
/*!\func
 *
 * \param no
 * \return no
 */
int CmdFieldsModel::rowCount ( const QModelIndex & ) const
{
    Log::add(Log::LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    return rows;
}
/*!\func
 *
 * \param no
 * \return no
 */
int CmdFieldsModel::columnCount ( const QModelIndex &) const
{
   Log::add(Log::LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    return columns;
}
/*!\func
 *
 * \param no
 * \return no
 */
QVariant CmdFieldsModel::data ( const QModelIndex &index, int role) const
{
    Log::add(Log::LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    if (!index.isValid())
	 return QVariant();
    if (role != Qt::DisplayRole && role != Qt::EditRole)
	 return QVariant();
    switch(index.column())
    {
	case 0:
	    if (role == Qt::DisplayRole)
	    {
		    if (inputs[index.row()].getRw())
			    return  "write";
		    else
			    return  "read";
	    }
	    else
		    return  inputs[index.row()].getRw();
	    case 1:
	    if (role == Qt::DisplayRole)
	    {
		    if (inputs[index.row()].getWaitAnswer())
			    return  "yes";
		    else
			    return  "no";
	    }
	    else
		    return  inputs[index.row()].getWaitAnswer();
	case 2:
	    if (role == Qt::DisplayRole)
	    {
		    if (inputs[index.row()].getIncrement())
			    return  "yes";
		    else
			    return  "no";
	    }
	    else
		    return  inputs[index.row()].getIncrement();
	case 3:
	    if (role == Qt::DisplayRole)
	    {
		    return  "0x" + QString::number(inputs[index.row()].getAddress(), 16);
	    }
	    else
		    return  inputs[index.row()].getAddress();
	case 4:
		    QByteArray data = inputs[index.row()].getData();
		QString text ("0x");
		for (int i = 0; i < data.count(); i++)
		{
			QString digit = QString::number(data[i], 16);
			if (digit.length() < 2)digit = "0" + digit;
			if (digit.length() > 2)digit = digit.right(2);
			text += digit;
		}
		if (text.length() == 2)text += "0";
		text+="h";
		return  text;
    }
    return "!";
}
/*!\func
 *
 * \param no
 * \return no
 */
bool CmdFieldsModel::insertRow ( int row, const QModelIndex & parent)
{
    Log::add(Log::LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    beginInsertRows(parent,rows,rows);
    inputs.insert(row, Block(0,0,0,0));
    rows++;
    endInsertRows();
    return true;
}
/*!\func
 *
 * \param no
 * \return no
 */
bool CmdFieldsModel::setData ( const QModelIndex & index, const QVariant & value, int role)
{
   Log::add(Log::LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    if (role != Qt::EditRole)
	 return false;
    bool result = false;
    switch(index.column())
    {
	case 0:
	    inputs[index.row()].setRw(value.toInt());
	    result = true;
	    break;
	case 1:
	    inputs[index.row()].setWaitAnswer(value.toInt());
	    result = true;
	    break;
    case 2:
	inputs[index.row()].setIncrement(value.toInt());
	result = true;
	break;
    case 3:
	inputs[index.row()].setAddress(value.toInt());
	result = true;
	break;
    case 4:
	inputs[index.row()].setData(value.toByteArray());
	result = true;
	break;
    }
    if (result)
    {
	emit dataChanged(index, index);
}
    return result;
}
/*!\func
 *
 * \param no
 * \return no
 */
Qt::ItemFlags CmdFieldsModel::flags(const QModelIndex &index) const
{
    Log::add(Log::LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
     if (!index.isValid())
	 return 0;
     return Qt::ItemIsEditable |Qt::ItemIsEnabled | Qt::ItemIsSelectable;//
}
/*!\func
 *
 * \param no
 * \return no
 */
QVariant CmdFieldsModel::headerData ( int section, Qt::Orientation orientation, int role) const
{
    Log::add(Log::LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    if (role != Qt::DisplayRole)
	 return QVariant();
    if (orientation == Qt::Vertical)
	 return QVariant();
    switch(section)
    {
	case 0:
	    return qApp->translate("MainWindow", "R/W");
	case 1:
	    return qApp->translate("MainWindow", "Answr");
    case 2:
	return qApp->translate("MainWindow", "Inc");
    case 3:
	return qApp->translate("MainWindow", "Addr");
    case 4:
	return qApp->translate("MainWindow", "Data");
    }
    return QVariant();
}
/*!\func
 *
 * \param no
 * \return no
 */
const QList<Block>& CmdFieldsModel::getList()
{
   Log::add(Log::LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    return inputs;
}
/*!\func CmdFieldsDelegate::CmdFieldsDelegate
 * конструктор
 * \param нет
 * \return нет
 */
CmdFieldsDelegate::CmdFieldsDelegate(QObject *)
{
   Log::add(Log::LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
}
/*!\func CmdFieldsDelegate::createEditor
 * создает редактор ячейки
 * \param нет
 * \return нет
 */
QWidget *CmdFieldsDelegate::createEditor(QWidget *parent,
     const QStyleOptionViewItem &/* option */,
     const QModelIndex & index) const
{
    Log::add(Log::LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    switch(index.column()) {
	case 0:
	{
		    QComboBox *editor = new QComboBox(parent);
		    editor->addItem("read");
		    editor->addItem("write");
		    return editor;
	}
	case 1:
	{
		    QComboBox *editor = new QComboBox(parent);
		    editor->addItem("no");
		    editor->addItem("yes");
		    return editor;
	}
    case 2:
    {
		QComboBox *editor = new QComboBox(parent);
		editor->addItem("static");
		editor->addItem("increment");
		return editor;
    }
    case 3:
    {
		QLineEdit *editor = new QLineEdit(parent);
		return editor;
    }
    case 4:
    {
		QLineEdit *editor = new QLineEdit(parent);
		return editor;
    }
    }
    return 0;
}
/*!\func CmdFieldsDelegate::createEditor
 * установить данные в виджет
 * \param нет
 * \return нет
 */
void CmdFieldsDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
   Log::add(Log::LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    switch(index.column()) {
    case 0:
    case 1:
    case 2:
    {
	     Log::add(Log::LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	     int value = index.model()->data(index, Qt::EditRole).toInt();
	     QComboBox *spinBox = static_cast<QComboBox*>(editor);
	     spinBox->setCurrentIndex(value);
     }
     break;
    case 3:
    {
	Log::add(Log::LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	QString value = "0x" + QString::number (index.model()->data(index, Qt::EditRole).toInt (), 16);
	QLineEdit *spinBox = static_cast<QLineEdit*>(editor);
	spinBox->setText(value);
    }
    break;
    case 4:
    {
	Log::add(Log::LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
	QString value = index.model()->data(index, Qt::EditRole).toString();
	QLineEdit *spinBox = static_cast<QLineEdit*>(editor);
	spinBox->setText(value);
    }
    break;
    }
}
/*!\func CmdFieldsDelegate::setModelData
 * установить данные в модель
 * \param нет
 * \return нет
 */
void CmdFieldsDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
				    const QModelIndex &index) const
{
    Log::add(Log::LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
    switch(index.column()) {
	case 0:
    case 1:
    case 2:
	{
		QComboBox *spinBox = static_cast<QComboBox*>(editor);
		QString value = QString::number(spinBox->currentIndex());
		model->setData(index, value, Qt::EditRole);
	}
	break;
    case 3:
	{
		bool ok;
		QLineEdit *spinBox = static_cast<QLineEdit*>(editor);
		QString value = spinBox->text();
		model->setData(index, value.toInt(&ok, 16), Qt::EditRole);
	}
	break;
	case 4:
	{
		QLineEdit *spinBox = static_cast<QLineEdit*>(editor);
		QString value = spinBox->text ();
		if(value.startsWith("0x"))value = value.right(value.length() - 2);
		int base = 16;
		if (value.endsWith("h"))
		{
			base = 16;
			value = value.left(value.length()-1);
		}
		else
		if (value.endsWith("d"))
		{
			base = 10;
			value = value.left(value.length()-1);
		}
		else
		if (value.endsWith("b"))
		{
			base = 2;
			value = value.left(value.length()-1);
		}
		bool ok;
		int data_index = 0;
		QByteArray data(value.length(), 0);
		if (base == 16)
		{
			while (value.length()%2)value = "0" + value;
			data.resize(value.length()/2);
			for (int i = 0; i < value.length()-1;i+=2)
				data[data_index++] = QString("0x" + value[i] + value[i+1]).toInt(&ok, base);
		}
		else
		if (base == 10)
		{
			for (int i = 0; i < value.length();i++)
				data[data_index++] =  QString (value[i]).toInt ();
		}
		else
		if (base == 2)
		{
			while(value.length() < 8)value = "0" + value;
			while(value.length() % 8)value = "0" + value;
			data.resize(value.length()/8);
			for (int i = 0; i < value.length()-7;i+=8)
			{
				QString tmp("");
				for (int k = 0; k < 8; k++)
					tmp += value[i+k];
				data[data_index++] = QString(tmp).toInt(&ok, base);
			}
		}
		model->setData(index, data, Qt::EditRole);
	}
	break;
    }
}
/*!\func CmdFieldsDelegate::updateEditorGeometry
 * изменить геометрию
 * \param нет
 * \return нет
 */
void CmdFieldsDelegate::updateEditorGeometry(QWidget *editor,
     const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
     Log::add(Log::LOG_DEBUG, QString(__FUNCTION__) + " <" + QString::number(__LINE__) + ">");
     editor->setGeometry(option.rect);
}

