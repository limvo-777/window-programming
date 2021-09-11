#ifndef CREATE_THREAD
#define CREATE_THREAD

DWORD WINAPI MyThreadFunction(LPVOID lpParam)
{
    // printf("Parameter: %u\n",*(DWORD *)lpParam);
    
    //new thread start
    while(1)
    {
        DWORD ** teb_address= (DWORD **) NtCurrentTeb();
        DWORD ** peb_address =(DWORD **) *(teb_address + 0x60/8);
        DWORD global_flag =*((byte *)peb_address + 0xbc); // 8로 나눠지지 않음 (0xbc:188)

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
    //&ID : thread ID 주소

    if(hThread==NULL) //CreatedThread fail
    {
        printf("\nCreateThread Failed\n");
    }else{
        printf("\nCreate Thread for Anti-Debugging\n");
    }
    
    CloseHandle(hThread);

    printf("\nStart Keyboard Logging?\n");
    system("pause");

    return 0;
}
#endif