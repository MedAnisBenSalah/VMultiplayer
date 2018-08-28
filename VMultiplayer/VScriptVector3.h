/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: VScriptVector3.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef VSCRIPTVECTOR3_H
#define VSCRIPTVECTOR3_H

class VScriptVector3
{
public:
	float		fX;
	DWORD		dwPadX;
	float		fY;
	DWORD		dwPadY;
	float		fZ;
	DWORD		dwPadZ;

	// Default constructors
	VScriptVector3()
	{
		fX = fY = fZ = 0;
		dwPadX = dwPadY = dwPadZ = 0;
	};

	VScriptVector3(float fX, float fY, float fZ)
	{
		this->fX = fX;
		this->fY = fY;
		this->fZ = fZ;
		dwPadX = dwPadY = dwPadZ = 0;
	};

	VScriptVector3(CVector3 vecInput)
	{
		fX = vecInput.fX;
		fY = vecInput.fY;
		fZ = vecInput.fZ;
		dwPadX = dwPadY = dwPadZ = 0;
	};
};

#endif