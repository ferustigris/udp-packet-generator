#include "ipacket.h"
#include "packet.h"
#include "errors.h"
#include "simplepacket.h"

/*
  шаблон абстрактная фабрика: создает пакет либо обычный, либо нашего формата
  */
IPacket*IPacket::getPacket (const QByteArray data)
{
	IPacket *packet = 0;
	try {
		packet = new Packet (data);
	}
	catch (ECommonError err) {
		packet = new SimplePacket (data);
	}
	return packet;
}
