/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: DataStreamFactory.h
-- Project: Network
-- Author(s): OrMisicL

=============================================================*/

#ifndef DATASTREAMFACTORY_H
#define DATASTREAMFACTORY_H

class CDataStreamFactory
{
public:
	static CDataStream *GetInstance();
	static CDataStream *GetInstance(unsigned char *pucData, unsigned int uiLength);
	static void DestroyInstance(CDataStream *pInstance);
};

#endif