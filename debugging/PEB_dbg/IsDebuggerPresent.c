#include <stdio.h>
#include <winnt.h>
#include <windows.h>

int main(int argc,char** argv)
{
    BOOL debug_flag=IsDebuggerPresent();
    printf("Debug Flag: %d\n",debug_flag);

    printf("*** Press Enter");
    getchar();

    return 0;
}