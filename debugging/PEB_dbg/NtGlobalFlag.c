#include <stdio.h>
#include <winnt.h>
#include <windows.h>

int main(int argc,char** argv)
{
    char ** teb_address= NtCurrentTeb();
    printf("TEB Address: %x\n", teb_address);

    char ** peb_address = *(teb_address + 0x30/4);
    printf("PEB Address: %x\n", peb_address);
    
    //NtGlobalFlag
    char ** global_flag =*(peb_address + 0x68/4);
    
    printf("Global Flags: %x\n",global_flag);

    if (global_flag==0){
        printf("Not debugged\n");

    }else{
        printf("Debugging Detected\n");
        system("pause");
    }

    system("pause");

    return 0;
}