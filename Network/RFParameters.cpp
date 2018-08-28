/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: RFParameters.cpp
-- Project: Network
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

using namespace RakNet;

CRFParameters::CRFParameters(BitStream *pBitStream, CNetSenderInfo *pSenderInfo)
{
	// Save the RF parameters
	m_pBitStream = pBitStream;
	m_pSenderInfo = pSenderInfo;
}

CRFParameters::~CRFParameters()
{

}




