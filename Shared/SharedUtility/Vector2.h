/* =========================================================
      V:Multiplayer - http://www.vmultiplayer.com

-- File: Vector2.h
-- Project: Shared
-- Author(s): OrMisicL

=============================================================*/

class CVector2
{
public:
	float		fX;
	float		fY;

	// Class constructors
	CVector2()
	{
		fX = 0.0f;
		fY = 0.0f;
	};

	CVector2(float _fX, float _fY)
	{
		fX = _fX;
		fY = _fY;
	};

	CVector2 operator + (const CVector2& vecRight) const
	{
		return CVector2(fX + vecRight.fX, fY + vecRight.fY);
	}

	CVector2 operator - (const CVector2& vecRight) const
	{
		return CVector2(fX - vecRight.fX, fY - vecRight.fY);
	}

	CVector2 operator * (const CVector2& vecRight) const
	{
		return CVector2(fX * vecRight.fX, fY * vecRight.fY);
	}

	CVector2 operator * (float fRight) const
	{
		return CVector2(fX * fRight, fY * fRight);
	}

	CVector2 operator / (const CVector2& vecRight) const
	{
		return CVector2(fX / vecRight.fX, fY / vecRight.fY);
	}

	CVector2 operator - () const
	{
		return CVector2(-fX, -fY);
	}

	void operator += (float fRight)
	{
		fX += fRight;
		fY += fRight;
	}

	void operator += (const CVector2& vecRight)
	{
		fX += vecRight.fX;
		fY += vecRight.fY;
	}

	void operator -= (float fRight)
	{
		fX -= fRight;
		fY -= fRight;
	}

	void operator -= (const CVector2& vecRight)
	{
		fX -= vecRight.fX;
		fY -= vecRight.fY;
	}

	void operator *= (float fRight)
	{
		fX *= fRight;
		fY *= fRight;
	}

	void operator *= (const CVector2& vecRight)
	{
		fX *= vecRight.fX;
		fY *= vecRight.fY;
	}

	void operator /= (float fRight)
	{
		fX /= fRight;
		fY /= fRight;
	}

	void operator /= (const CVector2& vecRight)
	{
		fX /= vecRight.fX;
		fY /= vecRight.fY;
	}

	bool operator== (const CVector2& param) const
	{
		return ((fabs(fX - param.fX) < 0.0001f) &&
			(fabs(fY - param.fY) < 0.0001f));
	}

	bool operator!= (const CVector2& param) const
	{
		return ((fabs(fX - param.fX) >= 0.0001f) ||
			(fabs(fY - param.fY) >= 0.0001f));
	}
};
