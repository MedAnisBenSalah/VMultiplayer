/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: VThread.h
-- Project: Client
-- Author(s): OrMisicL

=============================================================*/

#ifndef VTHREAD_H
#define VTHREAD_H

enum eVThreadState
{
	VTHREAD_STATE_IDLE,
	VTHREAD_STATE_RUNNING,
	VTHREAD_STATE_STOPPED
};

#pragma pack(push, 1)
class VScrThreadContext
{
public:
	PAD(pad0, 0x8);							// 0x00000 - 0x00008
	int					iId; 				// 0x00008 - 0x0000C 
	DWORD				dwScriptHash; 		// 0x0000C - 0x00010 
	eVThreadState		state; 				// 0x00010 - 0x00014 
	DWORD				dwIP; 				// 0x00014 - 0x00018 
	DWORD				dwFrameSP; 			// 0x00018 - 0x0001C  
	DWORD				dwSP; 				// 0x0001C - 0x00020  
	DWORD				dwTimerA; 			// 0x00020 - 0x00024  
	DWORD				dwTimerB; 			// 0x00024 - 0x00028  
	DWORD				dwTimerC; 			// 0x00028 - 0x0002C   
	DWORD				dwUnknown1;			// 0x0002C - 0x00030 // dwUnknown1 and 2 equals -1 when init
	DWORD				dwUnknown2;			// 0x00030 - 0x00034
	PAD(pad1, 0x34);						// 0x00034 - 0x00068
	DWORD				dwSet1;				// 0x00068 - 0x0006C 
	PAD(pad2, 0x44);						// 0x0006C - 0x000B0
	// Size = 0xB0
};
#pragma pack(pop)

#pragma pack(push, 1)
class VScrThread : public VScrThreadContext
{
public:
	// VScrThreadContext					// 0x00000 - 0x000B0
	void			*pStack;				// 0x000B0 - 0x000B8		
	PAD(pad0, 0x10);						// 0x000B8 - 0x000C8
	char			*pszExitMessage;		// 0x000C8 - 0x000D0
	// Size = 0xD0
};
#pragma pack(pop)

#pragma pack(push, 1)
class VGtaThread : public VScrThread
{
public:
	// VScrThread							// 0x00000 - 0x000D0
	char				szName[64];			// 0x000D0 - 0x00110
	PAD(pad3, 0x48);						// 0x00110 - 0x00158
	// Size = 0x158
};
#pragma pack(pop)

class CVThread : public CVObjectBase<VGtaThread>
{
public:
	CVThread(VGtaThread *pThread);
	~CVThread();

	int					GetId();
	void				SetId(int iId);
	eVThreadState		GetState();
	void				SetState(eVThreadState state);
	void				GetName(char *szName);
	void				SetName(char *szName);

private:
};

#endif