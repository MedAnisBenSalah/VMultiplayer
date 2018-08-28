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
	virtual BYTE				GetMessageID() = 0;
	virtual BitStream			*GetBitStream() = 0;
	virtual CNetSenderInfo		*GetSenderInfo() = 0;
};

#endif