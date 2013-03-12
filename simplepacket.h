#ifndef SIMPLEPACKET_H
#define SIMPLEPACKET_H
#include "ipacket.h"

//! class - packet
class SimplePacket: public IPacket
{
public:
    SimplePacket(const QByteArray);
    QByteArray getBody() const;
    QString toText () const;
private:
    QByteArray body;
};
#endif // SIMPLEPACKET_H
