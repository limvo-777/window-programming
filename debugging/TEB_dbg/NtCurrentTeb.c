#include <stdio.h>
#include <winnt.h>
#include <windows.h>

int main(int argc,char** argv)
{
    char ** teb_address=NtCurrentTeb();
    printf("TEB Address: %x\n", teb_address);

    system("pause");
    return 0;
}