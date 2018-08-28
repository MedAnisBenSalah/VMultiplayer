/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: ExceptionHandler.cpp
-- Project: Shared
-- Author(s): OrMisicL

=============================================================*/

#include "ExceptionHandler.h"

char CExceptionHandler::szPath[MAX_PATH];

void CExceptionHandler::Install(char *szTargetPath)
{
	// Save the path
	strcpy(szPath, szTargetPath);
	// Set the exception handler callback
#ifdef _WIN32
	//SetUnhandledExceptionFilter(ExceptionHandlerCallback);
	AddVectoredExceptionHandler(1, ExceptionHandlerCallback);
#else
	signal(SIGINT, ExceptionHandlerCallback);
	signal(SIGHUP, ExceptionHandlerCallback);
	signal(SIGTERM, ExceptionHandlerCallback);
#endif
}

void CExceptionHandler::GetExceptionName(DWORD dwCode, char *szOutput)
{
#ifdef _WIN32
	switch (dwCode)
	{
	case EXCEPTION_ACCESS_VIOLATION:
		strcpy(szOutput, "Access Violation");
		break;

	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
		strcpy(szOutput, "Array Bounds Exceeded");
		break;

	case EXCEPTION_BREAKPOINT:
		strcpy(szOutput, "Breakpoint");
		break;

	case EXCEPTION_DATATYPE_MISALIGNMENT:
		strcpy(szOutput, "Datatype Misalignment");
		break;

	case EXCEPTION_FLT_DENORMAL_OPERAND:
		strcpy(szOutput, "Float Denormal Operand");
		break;

	case EXCEPTION_FLT_DIVIDE_BY_ZERO:
		strcpy(szOutput, "Float Devide By Zero");
		break;

	case EXCEPTION_FLT_INEXACT_RESULT:
		strcpy(szOutput, "Float Inexact Result");
		break;

	case EXCEPTION_FLT_INVALID_OPERATION:
		strcpy(szOutput, "Float Invalid Operation");
		break;

	case EXCEPTION_FLT_OVERFLOW:
		strcpy(szOutput, "Float Overflow");
		break;

	case EXCEPTION_FLT_STACK_CHECK:
		strcpy(szOutput, "Float Stack Check");
		break;

	case EXCEPTION_FLT_UNDERFLOW:
		strcpy(szOutput, "Float Underflow");
		break;

	case EXCEPTION_ILLEGAL_INSTRUCTION:
		strcpy(szOutput, "Illegal Instruction");
		break;

	case EXCEPTION_IN_PAGE_ERROR:
		strcpy(szOutput, "In Page Error");
		break;

	case EXCEPTION_INT_DIVIDE_BY_ZERO:
		strcpy(szOutput, "Integer Divide By Zero");
		break;

	case EXCEPTION_INT_OVERFLOW:
		strcpy(szOutput, "Integer Overflow");
		break;

	case EXCEPTION_INVALID_DISPOSITION:
		strcpy(szOutput, "Invalid Disposition");
		break;

	case EXCEPTION_NONCONTINUABLE_EXCEPTION:
		strcpy(szOutput, "Noncontinuable Exception");
		break;

	case EXCEPTION_PRIV_INSTRUCTION:
		strcpy(szOutput, "Private Instruction");
		break;

	case EXCEPTION_SINGLE_STEP:
		strcpy(szOutput, "Single Step");
		break;

	case EXCEPTION_STACK_OVERFLOW:
		strcpy(szOutput, "Stack Overflow");
		break;

	default:
		strcpy(szOutput, "Unknown");
		break;
	}
#endif
}

#ifdef _WIN32
long WINAPI CExceptionHandler::ExceptionHandlerCallback(_EXCEPTION_POINTERS *pExceptionInfo)
{
#ifdef _WIN32
	// Don't process if the exception is continuable
	if (!pExceptionInfo->ExceptionRecord->ExceptionFlags)
		return EXCEPTION_EXECUTE_HANDLER;
#endif

	// Get the current time
	SYSTEMTIME systemTime;
	GetSystemTime(&systemTime);
	// Create the file name
	char szFileName[MAX_PATH];
	sprintf(szFileName, "CrashDump_%d-%d-%d_%d.%d.%d.txt", systemTime.wDay, systemTime.wMonth, systemTime.wYear, systemTime.wHour, systemTime.wMinute, systemTime.wSecond);
	// Create the full path
	char szFullPath[MAX_PATH];
	sprintf(szFullPath, "%s\\%s", szPath, szFileName);
	// Open the log file
	FILE *pFile = fopen(szFullPath, "w");
	// Make sure the file is opened
	if (!pFile)
		return EXCEPTION_EXECUTE_HANDLER;

#ifdef VMULTIPLAYER_CLIENT
	// Get the exception name
	char szExceptionName[64];
	GetExceptionName(pExceptionInfo->ExceptionRecord->ExceptionCode, szExceptionName);
	// Write the exception informations
	fprintf(pFile, "======================== V:Multiplayer Exception Handler ===============================\n");
	fprintf(pFile, "Exception: %s (%d)\nAddress: 0x%lp\n\n", szExceptionName, pExceptionInfo->ExceptionRecord->ExceptionCode, pExceptionInfo->ExceptionRecord->ExceptionAddress);
	fprintf(pFile, "Registers:\n");
	fprintf(pFile, "RAX: 0x%lp - RBX: 0x%lp - RCX: 0x%lp - RDX: 0x%lp\nRSI: 0x%lp - RDI: 0x%x - RBP: 0x%lp - RSP: 0x%lp\nR8: 0x%lp - R9: 0x%x - R10: 0x%lp - R11: 0x%lp\nR12: 0x%lp - R13: 0x%x - R14: 0x%lp - R15: 0x%lp\n\n", 
		pExceptionInfo->ContextRecord->Rax, pExceptionInfo->ContextRecord->Rbx, pExceptionInfo->ContextRecord->Rcx,
		pExceptionInfo->ContextRecord->Rdx, pExceptionInfo->ContextRecord->Rsi, pExceptionInfo->ContextRecord->Rdi,
		pExceptionInfo->ContextRecord->Rbp, pExceptionInfo->ContextRecord->Rsp, pExceptionInfo->ContextRecord->R8, 
		pExceptionInfo->ContextRecord->R9, pExceptionInfo->ContextRecord->R10, pExceptionInfo->ContextRecord->R11,
		pExceptionInfo->ContextRecord->R12, pExceptionInfo->ContextRecord->R13, pExceptionInfo->ContextRecord->R14, 
		pExceptionInfo->ContextRecord->R15);

	DWORD64 dwEsp = pExceptionInfo->ContextRecord->Rsp;
	fprintf(pFile, "Stack:\n");
	fprintf(pFile, "0x0: 0x%lp - 0x4: 0x%lp - 0x8: 0x%lp - 0xC: 0x%lp - 0x10: 0x%lp - 0x14: 0x%lp\n0x18: 0x%lp - 0x1C: 0x%lp - 0x20: 0x%lp\n", *(DWORD64 *)(dwEsp), *(DWORD64 *)(dwEsp + 4),
		*(DWORD64 *)(dwEsp + 8), *(DWORD64 *)(dwEsp + 12), *(DWORD64 *)(dwEsp + 16), *(DWORD64 *)(dwEsp + 20), *(DWORD64 *)(dwEsp + 24), *(DWORD64 *)(dwEsp + 28), *(DWORD64 *)(dwEsp + 32));

#else
#endif
	fprintf(pFile, "\nLibraries:\n");
#ifdef _WIN32
	// Get a list of all the modules in this process.
	HMODULE hModules[1024];
	DWORD dwModulesSize;
	if (EnumProcessModulesEx(GetModuleHandle(NULL), hModules, sizeof(hModules), &dwModulesSize, LIST_MODULES_ALL))
	{
		// Loop through all the modules
		for (int i = 0; i < (dwModulesSize / sizeof(HMODULE)); i++)
		{
			// Get the full path to the module's file.
			TCHAR szModuleName[MAX_PATH];
			if (GetModuleFileNameEx(GetModuleHandle(NULL), hModules[i], szModuleName, sizeof(szModuleName) / sizeof(TCHAR)))
				// Print the module name and handle value.
				fprintf(pFile, "%s (0x%lp)\n", szModuleName, (DWORD64)hModules[i]);
		}
	}
#endif
	fprintf(pFile, "\n");
	fprintf(pFile, "======================== V:Multiplayer Exception Handler ===============================");
	// Close the file
	fclose(pFile);
	// Display an error message and exit
#ifdef VMULTIPLAYER_CLIENT
	char *szName = "V:Multiplayer";
#else
	char *szName = "V:Multiplayer Server";
#endif
	char szMessage[256];
	sprintf(szMessage, "%s has crashed, a dump log was saved in \"%s\".", szName, szFileName);
#ifdef _WIN32
	MessageBox(NULL, szMessage, "V:Multiplayer error", MB_OK | MB_ICONERROR);
	ExitProcess(0);
#endif
	return EXCEPTION_EXECUTE_HANDLER;
}
#else 
void CExceptionHandler::ExceptionHandlerCallback(int signum)
{

}
#endif 