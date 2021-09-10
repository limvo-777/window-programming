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

        //thread 생성 안할 시
        //cmp dword ptr ss:[rbp-34],70 -> 같으면 zf 1, cf 0
        //jne hookmain.40160E -> zf 0이면 jump : zf 0으로 수정 시 우회 가능
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
        printf("CreateThread Success\n");
    }
    
    CloseHandle(hThread);

    system("pause");

    return 0;
}