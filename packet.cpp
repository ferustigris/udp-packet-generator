#include "packet.h"
#include "errors.h"

/*!\func
 * constructor
 * \param no
 * \return  no
 */
Packet::Packet(const qint32 id, const QList<Block> &cmd)
{
    this->cmd = cmd;
    this->id = id;
}
/*!\func
 * constructor
 * \param no
 * \return  no
 */
Packet::Packet(const QByteArray data)
{
	qint8 count = 0, format = 0;
	qint16 len = sizeof (count) + sizeof (id) + sizeof (format),
	shift = 0;
	if(data.size() < len)throw ECommonError("Size too short!");
	memcpy(&id, data.data()+shift, sizeof(id));
	shift += sizeof(id);
	memcpy(&format, data.data()+shift, sizeof(format));
	shift += sizeof(format);
	memcpy(&count, data.data()+shift, sizeof(count));
	shift += sizeof(count);
	for(int i = 0;(i < count)&&(shift < data.size()); i++)
	{
		QByteArray forBlock(data.size()-shift, 0);
		memcpy(forBlock.data(), shift + data.data(), forBlock.size());
		cmd.append(Block(forBlock));
		shift += cmd[cmd.count() - 1].getBody().size();
	}
}
/*!\func
 * packet's body
 * \param no
 * \return  no
 */
QByteArray Packet::getBody() const
{
	qint8 count = cmd.count(), shift = 0, format = 0,
	len = sizeof (count) + sizeof (id) + sizeof (format);
	QByteArray data(len ,0);
	memcpy (data.data() + shift, &id, sizeof (id));
	shift += sizeof (id);
	memcpy (data.data() + shift, &format, sizeof (format));
	shift += sizeof (format);
	memcpy (data.data() + shift, &count, sizeof (count));
	shift += sizeof (count);
	foreach (Block item, cmd)
	{
		QByteArray cmd = item.getBody();
		len += cmd.size();
		data.resize(len);
		memcpy (data.data() + shift, cmd.data(), cmd.size());
		shift += cmd.size();

	}
    return data;
}
/*!\func
 * packet's body in text format
 * \param no
 * \return  no
 */
QString Packet::toText () const
{
	qint8 count = cmd.count(), shift = 0, format = 0,
	len = sizeof (count) + sizeof (id) + sizeof (format);
	QByteArray data(len ,0);
	QString text("");
	memcpy (data.data() + shift, &id, sizeof (id));
	text += "";
	for (int i = shift; i < shift + sizeof (id); i++)
	{
		QString digit = QString::number(data[i], 16);
		if (digit.length() < 2)digit = "0" + digit;
		if (digit.length() > 2)digit = digit.right(2);
		text += "" + digit;
	}
	text += "-";
	shift += sizeof (id);
	memcpy (data.data() + shift, &format, sizeof (format));
	text += "";
	for (int i = shift; i < shift + sizeof (format); i++)
	{
		QString digit = QString::number(data[i], 16);
		if (digit.length() < 2)digit = "0" + digit;
		if (digit.length() > 2)digit = digit.right(2);
		text += "" + digit;
	}
	text += "";
	shift += sizeof (format);
	memcpy (data.data() + shift, &count, sizeof (count));
	text += "-";
	for (int i = shift; i < shift + sizeof (count); i++)
	{
		QString digit = QString::number(data[i], 16);
		if (digit.length() < 2)digit = "0" + digit;
		if (digit.length() > 2)digit = digit.right(2);
		text += "" + digit;
	}
	text += "";
	shift += sizeof (count);
	foreach (Block item, cmd)
	{
		text += "[" + item.toText() + "]";

	}
    return text;
}
