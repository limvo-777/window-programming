#include <stdio.h>
#include <winnt.h>
#include <windows.h>

// LDR 구조체에서 변경되는 힙 공간 찾기 힘듦
// Process Heap에서 FEEEFEEE로 변경되는 공간 찾기
int main(int argc,char** argv)
{
    char ** teb_address= NtCurrentTeb(); //TEB 주소
    printf("TEB Address: %x\n", teb_address);

    char ** peb_address = *(teb_address + 0x30/4); //PEB 주소
    printf("PEB Address: %x\n", peb_address);
    
    //ldr
    char ** ldr = *(peb_address+0x0c/4);

    //ProcessHeap 
    char ** process_heap = *(peb_address + 0x18/4);
    int flag = *(process_heap+0x40/4);
    int forceflag = *(process_heap+0x44/4);

    //water mark
    char * check_address = *(process_heap+0x60c0/4);
    printf("check address: %x\n", check_address);
    
    if((char *)check_address==0xFEEEFEEE){
        printf("Debugging Detected!\n");
    }else{
        printf("Not Debugged\n");
    }

    
    system("pause");

    return 0;
}