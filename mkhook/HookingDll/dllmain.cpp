// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.
#include "framework.h"

// hooking funcion


// 공유 메모리 설정
#pragma data_seg(".npdata")
// handle 변수 설정
HINSTANCE hModule_g = NULL; //instance(객체)에 대한 핸들
HHOOK hKeyHook = NULL; //hooking 핸들
HWND hWndBeeper = NULL; //beep 핸들
#pragma data_seg()

#pragma comment(linker,"/SECTION:.npdata,RWS")

//후킹 프로시저
LRESULT CALLBACK KeyHookProc(int nCode, WPARAM wParam, LPARAM lParam) //콜백 함수 
{
    if (nCode >= 0) {
        SendMessage(hWndBeeper, WM_USER + 1, wParam, lParam); 
        //키보드 후킹 후 nCode (키보드 값)이 들어오면 send message (wm user +1) 보냄
        //hWndBeeper = hWnd (WinProc : HookingExe) -> message를 핸들로 보냄
    }

    return CallNextHookEx(hKeyHook, nCode, wParam, lParam);
}

//후킹 설치
extern "C" __declspec(dllexport) void InstallHook(HWND hWnd) // C 기반 컴파일 + 키워드 + 함수
{
    hWndBeeper = hWnd;
    hKeyHook = SetWindowsHookEx(WH_KEYBOARD, KeyHookProc, hModule_g, NULL); 
    // 키보드 후킹 세팅 (이벤트 발생 시 KeyHookProc 수행)

}

//후킹 제거
extern "C" __declspec(dllexport) void UninstallHook(void)
{
    UnhookWindowsHookEx(hKeyHook);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        hModule_g = hModule;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

