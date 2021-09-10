#include <stdio.h>
#include <windows.h>
#include <conio.h>


//main 함수와 별개로 thread 실행을 위한 생성
DWORD WINAPI MyThreadFunction(LPVOID lpParam)
{
    // printf("Parameter: %u\n",*(DWORD *)lpParam);
    
    //new thread start
    while(1)
    {
        DWORD ** teb_address= (DWORD **) NtCurrentTeb();
        printf("TEB Address: %x\n", teb_address);

        DWORD ** peb_address =(DWORD **) *(teb_address + 0x60/8);
        printf("PEB Address: %x\n", peb_address);
        
        DWORD global_flag =*((byte *)peb_address + 0xbc); // 8로 나눠지지 않음 (0xbc:188)
        printf("Global Flags: %x\n",global_flag);

        if(global_flag == 0x70)
        {
            printf("Debugging Detected!!\n");
            //exit(-1);
            system("pause");
        }
    }
    return 0;
}

//thread 1
int create_thread()
{
    DWORD dwThreadId =1;
    DWORD dwThreadParam =1;

    //thread 2 생성
    HANDLE hThread = CreateThread(NULL,0,MyThreadFunction,&dwThreadParam,0,&dwThreadId);
    //NULL : handle 상속하지 않음
    //0 : stacksize (default)
    //MythreadFunction : 함수의 시작주소
    //&Param : 파라미터 주소 
    //0 : 즉시 thread 실행
    //&Param : thread ID 주소

    if(hThread==NULL) //CreatedThread fail
    {
        printf("CreateThread Failed\n");
    }else{
        printf("Create Thread for Anti-Debugging\n");
    }
    
    CloseHandle(hThread);

    printf("Start Keyboard Logging?\n");
    system("pause");

    return 0;
}