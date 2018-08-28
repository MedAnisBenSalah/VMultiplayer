/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: GUIButton.h
-- Project: GUI
-- Author(s): OrMisicL

=============================================================*/

#ifndef GUIBUTTON_H
#define GUIBUTTON_H

// Callback defition
typedef void( *ButtonPressed_t)(void *pObject);

class CGUIButton : public CGUIElement
{
public:
	virtual void RegisteCallback(ButtonPressed_t pfnButtonPressed, void *pObject = NULL);

	// This did not wanted to work so FUCK IT!!! we'll stick to the regular static functions for now
	/*template <typename T>
	void RegisterButtonCallback(void(T::*ButtonPressedCallback_t)(void *pUnused), T *pObject)
	{
		RegisteCallback((ButtonPressed_t)ButtonPressedCallback_t, pObject);
	};*/

	void RegisterButtonCallback(ButtonPressed_t pfnButtonPressed)
	{
		RegisteCallback(pfnButtonPressed);
	};

private:

};

#endif