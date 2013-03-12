#ifndef PACKET_H
#define PACKET_H
#include "block.h"
#include "ipacket.h"
#include <QList>

//! class - packet
class Packet: public IPacket
{
public:
    Packet(const qint32 id, const QList<Block> &cmd);
    Packet(const QByteArray data);
    QByteArray getBody() const;
    QString toText () const;
private:
    QList<Block> cmd;
    qint32 id;
};

#endif // PACKET_H
