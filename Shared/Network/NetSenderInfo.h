/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: NetSenderInfo.h
-- Project: Shared
-- Author(s): OrMisicL

=============================================================*/

#ifndef NETSENDERINFO_H
#define NETSENDERINFO_H

class CNetSenderInfo
{
public:
	virtual int		GetID() = 0;
	virtual char	*GetIP() = 0;
	virtual void	GetIP(char *szIP) = 0;
};

#endif