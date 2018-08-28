/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: RFParameters.h
-- Project: Network
-- Author(s): OrMisicL

=============================================================*/

#ifndef RFPARAMETERS_H
#define RFPARAMETERS_H

class CRFParameters
{
public:
	CRFParameters(RakNet::BitStream *pBitStream, CNetSenderInfo *pSenderInfo);
	~CRFParameters();

	virtual RakNet::BitStream	*GetBitStream() { return m_pBitStream; };
	virtual CNetSenderInfo		*GetSenderInfo() { return m_pSenderInfo; };

private:
	CNetSenderInfo			*m_pSenderInfo;
	RakNet::BitStream		*m_pBitStream;
};

#endif