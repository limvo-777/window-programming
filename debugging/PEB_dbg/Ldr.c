#include <stdio.h>
#include <winnt.h>
#include <windows.h>

int main(int argc,char** argv)
{
    char ** teb_address= NtCurrentTeb();
    printf("TEB Address: %x\n", teb_address);

    char ** peb_address = *(teb_address + 0x30/4);
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