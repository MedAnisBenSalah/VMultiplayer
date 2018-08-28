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
	virtual BitStream		*GetBitStream() = 0;
	virtual CNetSenderInfo	*GetSenderInfo() = 0;
};

#endif