/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: VStreaming.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef VSTREAMING_H
#define VSTREAMING_H

class CVStreaming
{
public:
	static void RequestIPL(char *szIPLName);

	static void RequestModel(DWORD dwModelHash);
	static bool HasModelLoaded(DWORD dwModelHash);
	static void GetModelInfoFromHash(DWORD dwModelHash, VModelInfo *pModelInfo);

private:
	static char m_szIPLName[128];
};

#endif