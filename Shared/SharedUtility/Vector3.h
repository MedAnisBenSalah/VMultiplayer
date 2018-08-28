/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: Vector3.h
-- Project: Shared
-- Author(s): OrMisicL

=============================================================*/

// Vector3 class
class CVector3
{
public:
	float		fX;
	float		fY;
	float		fZ;

	// Class constructors
	CVector3()
	{
		fX = 0.0;
		fY = 0.0;
		fZ = 0.0;
	};

	CVector3(float _fX, float _fY, float _fZ)
	{
		fX = _fX;
		fY = _fY;
		fZ = _fZ;
	};

	float Length(void) const
	{
		return sqrt((fX*fX) + (fY*fY) + (fZ*fZ));
	}

	CVector3 operator + (const CVector3& vecRight) const
	{
		return CVector3(fX + vecRight.fX, fY + vecRight.fY, fZ + vecRight.fZ);
	}

	CVector3 operator - (const CVector3& vecRight) const
	{
		return CVector3(fX - vecRight.fX, fY - vecRight.fY, fZ - vecRight.fZ);
	}

	CVector3 operator * (const CVector3& vecRight) const
	{
		return CVector3(fX * vecRight.fX, fY * vecRight.fY, fZ * vecRight.fZ);
	}

	CVector3 operator * (float fRight) const
	{
		return CVector3(fX * fRight, fY * fRight, fZ * fRight);
	}

	CVector3 operator / (const CVector3& vecRight) const
	{
		return CVector3(fX / vecRight.fX, fY / vecRight.fY, fZ / vecRight.fZ);
	}
	CVector3 operator / (float fRight) const
	{
		return CVector3(fX / fRight, fY / fRight, fZ / fRight);
	}

	CVector3 operator - () const
	{
		return CVector3(-fX, -fY, -fZ);
	}

	void operator += (float fRight)
	{
		fX += fRight;
		fY += fRight;
		fZ += fRight;
	}

	void operator += (const CVector3& vecRight)
	{
		fX += vecRight.fX;
		fY += vecRight.fY;
		fZ += vecRight.fZ;
	}

	void operator -= (float fRight)
	{
		fX -= fRight;
		fY -= fRight;
		fZ -= fRight;
	}

	void operator -= (const CVector3& vecRight)
	{
		fX -= vecRight.fX;
		fY -= vecRight.fY;
		fZ -= vecRight.fZ;
	}

	void operator *= (float fRight)
	{
		fX *= fRight;
		fY *= fRight;
		fZ *= fRight;
	}

	void operator *= (const CVector3& vecRight)
	{
		fX *= vecRight.fX;
		fY *= vecRight.fY;
		fZ *= vecRight.fZ;
	}

	void operator /= (float fRight)
	{
		fX /= fRight;
		fY /= fRight;
		fZ /= fRight;
	}

	void operator /= (const CVector3& vecRight)
	{
		fX /= vecRight.fX;
		fY /= vecRight.fY;
		fZ /= vecRight.fZ;
	}

	bool operator== (const CVector3& param) const
	{
		return ((fabs(fX - param.fX) < 0.0001f) &&
			(fabs(fY - param.fY) < 0.0001f) &&
			(fabs(fZ - param.fZ) < 0.0001f));
	}

	bool operator!= (const CVector3& param) const
	{
		return ((fabs(fX - param.fX) >= 0.0001f) ||
			(fabs(fY - param.fY) >= 0.0001f) ||
			(fabs(fZ - param.fZ) >= 0.0001f));
	}
};