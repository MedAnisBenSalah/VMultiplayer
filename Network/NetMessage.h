/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: NetMessage.h
-- Project: Network
-- Author(s): OrMisicL

=============================================================*/

#ifndef NETMESSAGE_H
#define NETMESSAGE_H

class CNetMessage
{
public:
	CNetMessage(RakNet::MessageID messageId, RakNet::BitStream *pBitStream, CNetSenderInfo *pSenderInfo);
	CNetMessage(RakNet::Packet *pPacket);
	CNetMessage();
	~CNetMessage();

	virtual RakNet::MessageID	GetMessageID() { return m_messageId; };
	virtual RakNet::BitStream	*GetBitStream() { return m_pBitStream; };
	virtual CNetSenderInfo		*GetSenderInfo() { return m_pSenderInfo; };

private:
	RakNet::MessageID	m_messageId;
	RakNet::BitStream	*m_pBitStream;
	CNetSenderInfo		*m_pSenderInfo;
};

#endif