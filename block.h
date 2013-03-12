#ifndef BLOCK_H
#define BLOCK_H

#include "command.h"
#include <QtGlobal>

class Block : public Command
{
public:
    Block(const bool rw, const bool waitAnswer, const bool increment, const qint8 answerBody);
    Block(const QByteArray d);
    QByteArray getBody () const;
    QByteArray getData() const;
    qint32 getAddress () const;
    void setAddress (const qint32 address);
    void setData(const QByteArray array);
    QString toText () const;
protected:
    qint16 crc(const QByteArray &array) const;
private:
    QByteArray data;
    qint32 address;
};

#endif // BLOCK_H
