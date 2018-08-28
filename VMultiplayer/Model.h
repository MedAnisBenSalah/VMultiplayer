/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Model.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef MODEL_H
#define MODEL_H

class CModel
{
public:
	CModel(DWORD dwModelHash);
	~CModel();

	bool Load();
	bool IsLoaded();

	bool SetHash(DWORD dwModelHash);
	DWORD GetModelHash() { return m_dwModelHash; };

	void GetModelInfo(VModelInfo *pModelInfo);

	CVModel *GetInterface() { return m_pInterface; };

private:
	CVModel		*m_pInterface;
	DWORD		m_dwModelHash;

};

#endif