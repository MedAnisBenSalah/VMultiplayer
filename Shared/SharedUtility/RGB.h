/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: RGB.h
-- Project: Shared
-- Author(s): OrMisicL

=============================================================*/

// We call this way to avoid the redifinition confusion for the compiler
class CGUIRGB
{
public:
	float		fRed;
	float		fGreen;
	float		fBlue;

	// Class constructors
	CGUIRGB()
	{
		fRed = 0.0f;
		fGreen = 0.0f;
		fBlue = 0.0f;
	};

	CGUIRGB(float fRed, float fGreen, float fBlue)
	{
		this->fRed = fRed;
		this->fGreen = fGreen;
		this->fBlue = fBlue;
	};

	CGUIRGB operator + (const CGUIRGB& rgbColour) const
	{
		return CGUIRGB(fRed + rgbColour.fRed, fGreen + rgbColour.fGreen, fBlue + rgbColour.fBlue);
	}

	CGUIRGB operator - (const CGUIRGB& rgbColour) const
	{
		return CGUIRGB(fRed - rgbColour.fRed, fGreen - rgbColour.fGreen, fBlue - rgbColour.fBlue);
	}

	CGUIRGB operator * (const CGUIRGB& rgbColour) const
	{
		return CGUIRGB(fRed * rgbColour.fRed, fGreen * rgbColour.fGreen, fBlue * rgbColour.fBlue);
	}

	CGUIRGB operator / (const CGUIRGB& rgbColour) const
	{
		return CGUIRGB(fRed / rgbColour.fRed, fGreen / rgbColour.fGreen, fBlue / rgbColour.fBlue);
	}

	CGUIRGB operator * (float fValue) const
	{
		return CGUIRGB(fRed * fValue, fGreen * fValue, fBlue * fValue);
	}

	CGUIRGB operator - () const
	{
		return CGUIRGB(-fRed, -fGreen, -fBlue);
	}

	void operator += (float fValue)
	{
		fRed += fValue;
		fGreen += fValue;
		fBlue += fValue;
	}

	void operator += (const CGUIRGB& rgbColour)
	{
		fRed += rgbColour.fRed;
		fGreen += rgbColour.fGreen;
		fBlue += rgbColour.fBlue;
	}

	void operator -= (float fValue)
	{
		fRed -= fValue;
		fGreen -= fValue;
		fBlue -= fValue;
	}

	void operator -= (const CGUIRGB& rgbColour)
	{
		fRed -= rgbColour.fRed;
		fGreen -= rgbColour.fGreen;
		fBlue -= rgbColour.fBlue;
	}

	void operator *= (float fValue)
	{
		fRed *= fValue;
		fGreen *= fValue;
		fBlue *= fValue;
	}

	void operator *= (const CGUIRGB& rgbColour)
	{
		fRed *= rgbColour.fRed;
		fGreen *= rgbColour.fGreen;
		fBlue *= rgbColour.fBlue;
	}

	void operator /= (float fValue)
	{
		fRed /= fValue;
		fGreen /= fValue;
		fBlue /= fValue;
	}

	void operator /= (const CGUIRGB& rgbColour)
	{
		fRed /= rgbColour.fRed;
		fGreen /= rgbColour.fGreen;
		fBlue /= rgbColour.fBlue;
	}

	bool operator== (const CGUIRGB& param) const
	{
		return ((fabs(fRed - param.fRed) < 0.0001f) &&
			(fabs(fGreen - param.fGreen) < 0.0001f) &&
			(fabs(fBlue - param.fBlue) < 0.0001f));
	}

	bool operator!= (const CGUIRGB& param) const
	{
		return ((fabs(fRed - param.fRed) >= 0.0001f) &&
			(fabs(fGreen - param.fGreen) >= 0.0001f) &&
			(fabs(fBlue - param.fBlue) >= 0.0001f));
	}
};
