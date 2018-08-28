/* =========================================================
		V:Multiplayer - http://www.vmultiplayer.com

-- File: Multiplayer.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

class CMultiplayer
{
	public:
		CMultiplayer();
		~CMultiplayer();

		bool GetInputState() { return m_bInputState; };
		void ToggleInput(bool bToggle) { m_bInputState = bToggle; };

		bool Initialize();
		void DoGameLoad();

		void ChangeInputState();
		static void ParseInput();

		void Process();


	private:
		bool						m_bInputState;
};

#endif