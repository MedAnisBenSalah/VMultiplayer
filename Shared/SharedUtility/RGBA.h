/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: RGB.h
-- Project: Shared
-- Author(s): OrMisicL

=============================================================*/

class CGUIRGBA
{
public:
	float		fRed;
	float		fGreen;
	float		fBlue;
	float		fAlpha;

	// Class constructors
	CGUIRGBA()
	{
		fRed = 0.0f;
		fGreen = 0.0f;
		fBlue = 0.0f;
		fAlpha = 0.0f;
	};

	CGUIRGBA(float fRed, float fGreen, float fBlue, float fAlpha)
	{
		this->fRed = fRed;
		this->fGreen = fGreen;
		this->fBlue = fBlue;
		this->fAlpha = fAlpha;
	};

	CGUIRGBA(CGUIRGB rgbColour, float fAlpha)
	{
		this->fRed = rgbColour.fRed;
		this->fGreen = rgbColour.fGreen;
		this->fBlue = rgbColour.fBlue;
		this->fAlpha = fAlpha;
	};

	CGUIRGBA(CGUIRGB rgbColour)
	{
		CGUIRGBA(rgbColour, 1.0f);
	};

	CGUIRGBA operator + (const CGUIRGBA& rgbColour) const
	{
		return CGUIRGBA(fRed + rgbColour.fRed, fGreen + rgbColour.fGreen, fBlue + rgbColour.fBlue, fAlpha + rgbColour.fAlpha);
	}

	CGUIRGBA operator - (const CGUIRGBA& rgbColour) const
	{
		return CGUIRGBA(fRed - rgbColour.fRed, fGreen - rgbColour.fGreen, fBlue - rgbColour.fBlue, fAlpha - rgbColour.fAlpha);
	}

	CGUIRGBA operator * (const CGUIRGBA& rgbColour) const
	{
		return CGUIRGBA(fRed * rgbColour.fRed, fGreen * rgbColour.fGreen, fBlue * rgbColour.fBlue, fAlpha * rgbColour.fAlpha);
	}

	CGUIRGBA operator / (const CGUIRGBA& rgbColour) const
	{
		return CGUIRGBA(fRed / rgbColour.fRed, fGreen / rgbColour.fGreen, fBlue / rgbColour.fBlue, fAlpha / rgbColour.fAlpha);
	}

	CGUIRGBA operator * (float fValue) const
	{
		return CGUIRGBA(fRed * fValue, fGreen * fValue, fBlue * fValue, fAlpha * fValue);
	}

	CGUIRGBA operator - () const
	{
		return CGUIRGBA(-fRed, -fGreen, -fBlue, -fAlpha);
	}

	void operator += (float fValue)
	{
		fRed += fValue;
		fGreen += fValue;
		fBlue += fValue;
	}

	void operator += (const CGUIRGBA& rgbColour)
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

	void operator -= (const CGUIRGBA& rgbColour)
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

	void operator *= (const CGUIRGBA& rgbColour)
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

	void operator /= (const CGUIRGBA& rgbColour)
	{
		fRed /= rgbColour.fRed;
		fGreen /= rgbColour.fGreen;
		fBlue /= rgbColour.fBlue;
	}

	bool operator== (const CGUIRGBA& param) const
	{
		return ((fabs(fRed - param.fRed) < 0.0001f) &&
			(fabs(fGreen - param.fGreen) < 0.0001f) &&
			(fabs(fBlue - param.fBlue) < 0.0001f) &&
			(fabs(fAlpha - param.fAlpha) < 0.0001f));
	}

	bool operator!= (const CGUIRGBA& param) const
	{
		return ((fabs(fRed - param.fRed) >= 0.0001f) &&
			(fabs(fGreen - param.fGreen) >= 0.0001f) &&
			(fabs(fBlue - param.fBlue) >= 0.0001f) &&
			(fabs(fAlpha - param.fAlpha) >= 0.0001f));
	}
};
