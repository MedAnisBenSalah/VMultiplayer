/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: NetSenderInfo.cpp
-- Project: Network
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

using namespace RakNet;

CNetMessage::CNetMessage()
{
	// Reset
	m_pBitStream = NULL;
	m_pSenderInfo = NULL;
	m_messageId = ID_INVALID_MESSAGE;
}

CNetMessage::CNetMessage(RakNet::MessageID messageId, BitStream *pBitStream, CNetSenderInfo *pSenderInfo)
{
	m_messageId = messageId;
	m_pBitStream = pBitStream;
	m_pSenderInfo = pSenderInfo;
}

CNetMessage::CNetMessage(RakNet::Packet *pPacket)
{
	m_messageId = pPacket->data[0];
	m_pBitStream = new BitStream(pPacket->data, pPacket->length, false);
	m_pSenderInfo = new CNetSenderInfo(pPacket->systemAddress);
}

CNetMessage::~CNetMessage()
{
	// Delete instances
	SAFE_DELETE(m_pBitStream);
	SAFE_DELETE(m_pSenderInfo);
}
