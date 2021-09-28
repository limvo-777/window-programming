// boanteam_call_dll.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "windows.h"

typedef int(*LPFNBOANTEAM)(void);

int main()
{
	HINSTANCE hDll = LoadLibrary(_T("C:\\5Works\\Code\\DLL\\boanteam\\x64\\Debug\\boanteam.dll"));
	if (NULL == hDll)
		return -1;

	LPFNBOANTEAM lpfnBoanTeam = (LPFNBOANTEAM)GetProcAddress(hDll, "fnboanteam");
	if (NULL == lpfnBoanTeam)
	{
		FreeLibrary(hDll);
		return -2;
	}

	int nResult = lpfnBoanTeam();
	printf("nResult(1) = %d \n", nResult);

	nResult = lpfnBoanTeam();
	printf("nResult(2)  = %d \n", nResult);

	FreeLibrary(hDll);
    return 0;
}

