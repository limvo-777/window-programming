// HookDLL.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"
#include <Windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>

#include "mhook-lib\mhook.h"

typedef BOOL(WINAPI *PWRITEFILE)(
	_In_        HANDLE       hFile,
	_In_        LPCVOID      lpBuffer,
	_In_        DWORD        nNumberOfBytesToWrite,
	_Out_opt_   LPDWORD      lpNumberOfBytesWritten,
	_Inout_opt_ LPOVERLAPPED lpOverlapped);

static PWRITEFILE g_pOrgWriteFile = NULL;

// WriteFile() 함수 호출시 사용하게 될 함수
// Copy From MSDN: https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=KO-KR&k=k(%22FILEAPI%2FWriteFile%22);k(WriteFile);k(DevLang-C%2B%2B);k(TargetOS-Windows)&rd=true
BOOL WINAPI BoanWriteFile(
	_In_        HANDLE       hFile,
	_In_        LPCVOID      lpBuffer,
	_In_        DWORD        nNumberOfBytesToWrite,
	_Out_opt_   LPDWORD      lpNumberOfBytesWritten,
	_Inout_opt_ LPOVERLAPPED lpOverlapped)
{
	char *pBufEnc = (char*)malloc(nNumberOfBytesToWrite);
	memset(pBufEnc, 'A', nNumberOfBytesToWrite);

#ifdef _DEBUG
	_tprintf(_T("BoanWriteFile(%d bytes) called\n"), nNumberOfBytesToWrite);
#endif

	BOOL bRet = TRUE;

	if (NULL != g_pOrgWriteFile)
		bRet = g_pOrgWriteFile(hFile, pBufEnc, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);

	free(pBufEnc);
	pBufEnc = NULL;

	return bRet;
}

// IAT hook을 이용한 API Hooking (Thread로 동작하기 위함)
// Ref: http://codefromthe70s.org/mhook.aspx
//      Mhook is freely distributed under an MIT license with support for x86 and x64. 
DWORD WINAPI InjectThreadProc(LPVOID lParam)
{
#ifdef _DEBUG
	AllocConsole();
	FILE* pCout = NULL;
	freopen_s(&pCout, "CONOUT$", "w", stdout);
#endif

	BOOL bDone = FALSE;

	g_pOrgWriteFile = (PWRITEFILE)GetProcAddress(GetModuleHandle(_T("kernel32.dll")), "WriteFile");
	if (NULL == g_pOrgWriteFile) {
#ifdef _DEBUG
		_tprintf(_T("GetProcAddress() - WriteFile failed\n"));
		goto _ERROR_CASE;
#endif
	}

	bDone = Mhook_SetHook((PVOID*)&g_pOrgWriteFile, BoanWriteFile);

#ifdef _DEBUG
_ERROR_CASE:
#endif

	if (bDone)
		::MessageBox(NULL, _T("API hook succeed"), _T("HookDLL"), MB_OK);
	else
		::MessageBox(NULL, _T("API hook failed"), _T("HookDLL"), MB_OK);

#ifdef _DEBUG
	FreeConsole();
	_fcloseall();
#endif

	return 0;
}
