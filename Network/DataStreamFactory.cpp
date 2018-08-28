/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: DataStreamFactory.cpp
-- Project: Network
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"


CDataStream *CDataStreamFactory::GetInstance()
{
	CDataStream *pDataStream = new CDataStream();
	return pDataStream;
}

CDataStream *CDataStreamFactory::GetInstance(unsigned char *pucData, unsigned int uiLength)
{
	CDataStream *pDataStream = new CDataStream(pucData, uiLength);
	return pDataStream;
}

void CDataStreamFactory::DestroyInstance(CDataStream *pInstance)
{
	SAFE_DELETE(pInstance);
}