#ifndef IPACKET_H
#define IPACKET_H
#include <QList>
#include <QString>

//! class - packet
class IPacket
{
public:
    virtual QByteArray getBody() const = 0;
    virtual QString toText () const = 0;
    static IPacket*getPacket (const QByteArray data);
};
#endif // IPACKET_H
