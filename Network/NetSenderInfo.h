/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: NetSenderInfo.h
-- Project: Network
-- Author(s): OrMisicL

=============================================================*/

#ifndef NETSENDERINFO_H
#define NETSENDERINFO_H

class CNetSenderInfo
{
public:
	CNetSenderInfo(RakNet::SystemAddress systemAddress);
	CNetSenderInfo(char *szIP, int iId);
	CNetSenderInfo();
	~CNetSenderInfo();

	virtual int		GetID() { return m_iNetworkId; };
	virtual char	*GetIP() { return (char *)&m_szNetworkIP; };
	virtual void	GetIP(char *szIP) { strcpy(szIP, m_szNetworkIP); };


private:
	int							m_iNetworkId;
	char						m_szNetworkIP[16];
	RakNet::SystemAddress		m_systemAddress;
};

#endif