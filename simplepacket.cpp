#include "simplepacket.h"

/*!\func
 * constructor
 * \param no
 * \return  no
 */
SimplePacket::SimplePacket(const QByteArray data)
{
	body = data;
}
/*!\func
 * packet's body
 * \param no
 * \return  no
 */
QByteArray SimplePacket::getBody() const
{
	return body;
}
/*!\func
 * packet's body in text
 * \param no
 * \return  no
 */
QString SimplePacket::toText () const
{
	QString text ("");
	for (int i = 0; i < body.length(); i++)
	{
		QString digit = QString::number(body[i], 16);
		if (digit.length() < 2)digit = "0" + digit;
		if (digit.length() > 2)digit = digit.right(2);
		text += "" + digit;
	}
	return text;
}
