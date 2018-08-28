/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: NetSenderInfo.cpp
-- Project: Network
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

using namespace RakNet;

CNetSenderInfo::CNetSenderInfo()
{
	// Reset
	strcpy(m_szNetworkIP, "");
	m_iNetworkId = INVALID_NETWORK_ID;
	m_systemAddress = 0;
}

CNetSenderInfo::CNetSenderInfo(RakNet::SystemAddress systemAddress)
{
	m_systemAddress = systemAddress;
	strcpy(m_szNetworkIP, systemAddress.ToString());
	m_iNetworkId = systemAddress.systemIndex;
}

CNetSenderInfo::CNetSenderInfo(char *szIP, int iId)
{
	m_systemAddress = 0;
	strcpy(m_szNetworkIP, szIP);
	m_iNetworkId = iId;
}

CNetSenderInfo::~CNetSenderInfo()
{

}
