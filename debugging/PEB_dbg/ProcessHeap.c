#include <stdio.h>
#include <winnt.h>
#include <windows.h>

int main(int argc,char** argv)
{
    char ** teb_address= NtCurrentTeb();
    printf("TEB Address: %x\n", teb_address);

    //메모리 주소 크기가 4씩 증가하기 때문에 
    char ** peb_address = *(teb_address + 0x30/4);
    printf("PEB Address: %x\n", peb_address);
    
    //ProcessHeap 
    char ** process_heap = *(peb_address + 0x18/4);
    int flag = *(process_heap+0x40/4);
    int forceflag = *(process_heap+0x44/4);
    printf("Flags: %x\nForceFlags: %x\n",flag,forceflag);

    if(flag==2){
        printf("Not Debbuged\n");
    }else{
        printf("Debugging Detected\n");
        system("pause");
    }

    system("pause");

    return 0;
}