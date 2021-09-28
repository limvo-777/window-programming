// HookAPI.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <Windows.h>

#include <tlhelp32.h>
DWORD GetPIDbyName(LPCTSTR strProcessName)
{
	HANDLE hProcessSnapshot = NULL;
	PROCESSENTRY32 pe32;
	DWORD dwResult = 0;

	// Take a snapshot of all processes in the system.
	hProcessSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hProcessSnapshot)
		return 0;

	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (FALSE == Process32First(hProcessSnapshot, &pe32))
	{
		CloseHandle(hProcessSnapshot);
		return 0;
	}

	do
	{
		//_tprintf(_T("PID [%s]\n"), pe32.szExeFile);
		if (0 == _tcscmp(strProcessName, pe32.szExeFile))
		{
			dwResult = pe32.th32ProcessID;
			break;
		}
	} while (Process32Next(hProcessSnapshot, &pe32));

	CloseHandle(hProcessSnapshot);

	return dwResult;
}

int main()
{
#ifdef _WIN64
	const TCHAR HOOK_DLL_NAME[] = _T("C:\\_Temp\\HookDLL.dll");
#else
	const TCHAR HOOK_DLL_NAME[] = _T("C:\\_Temp\\HookDLL.dll");
#endif

	DWORD dwPID = GetPIDbyName(_T("notepad.exe"));
	if (dwPID <= 0) {
		_tprintf(_T("notepad.exe is not found\n"));
		return -1;
	}

	HANDLE hProcess = NULL;
	LPVOID pProcessMemory = NULL;

	DWORD dwDLLNameLen = (DWORD)((_tcslen(HOOK_DLL_NAME) + 1) * sizeof(TCHAR));

	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);
	if (NULL == hProcess)
	{
		_tprintf(_T("OpenProcess\n"));
		return -2;
	}

	pProcessMemory = VirtualAllocEx(hProcess, NULL, dwDLLNameLen, MEM_COMMIT, PAGE_READWRITE);
	if (NULL == pProcessMemory)
	{
		CloseHandle(hProcess);
		_tprintf(_T("VirtualAllocEx failed\n"));
		return -3;
	}
	if (FALSE == WriteProcessMemory(hProcess, pProcessMemory, (LPVOID)HOOK_DLL_NAME, dwDLLNameLen, NULL))
	{
		VirtualFreeEx(hProcess, pProcessMemory, dwDLLNameLen, MEM_DECOMMIT);
		CloseHandle(hProcess);
		_tprintf(_T("WriteProcessMemory failed\n"));
		return -4;
	}

	HMODULE hDLL = GetModuleHandle(_T("kernel32.dll"));
	LPTHREAD_START_ROUTINE pThreadProc = NULL;
	HANDLE hThread = NULL;

	if (NULL == hDLL)
	{
		VirtualFreeEx(hProcess, pProcessMemory, dwDLLNameLen, MEM_DECOMMIT);
		CloseHandle(hProcess);
		_tprintf(_T("GetModuleHandle failed\n"));
		return -5;
	}
	pThreadProc = (LPTHREAD_START_ROUTINE)GetProcAddress(hDLL, "LoadLibraryW");
	if (NULL == pThreadProc)
	{
		VirtualFreeEx(hProcess, pProcessMemory, dwDLLNameLen, MEM_DECOMMIT);
		CloseHandle(hProcess);
		_tprintf(_T("GetProcAddress failed\n"));
		return -6;
	}

	hThread = CreateRemoteThread(hProcess, NULL, 0, pThreadProc, pProcessMemory, 0, NULL);
	if (NULL == hThread)
	{
		//CloseHandle(hDLL);
		VirtualFreeEx(hProcess, pProcessMemory, dwDLLNameLen, MEM_DECOMMIT);
		CloseHandle(hProcess);
		_tprintf(_T("CreateRemoteThread failed [%d]\n"), GetLastError());
		return -7;
	}

	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hThread);
	VirtualFreeEx(hProcess, pProcessMemory, dwDLLNameLen, MEM_DECOMMIT);
	CloseHandle(hProcess);

	_tprintf(_T("Injection DONE\n"));

	_gettch();

    return 0;
}

