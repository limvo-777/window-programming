#include <stdio.h>
#include <string.h>

#define logfile "log.txt"

int main(int argc, char ** argv)
{
    FILE *file;
    file = fopen(logfile,"wb");

    char * write_msg = "this is log file\0";
    fwrite(write_msg, strlen(write_msg), 1, file);

    fclose(file);

    return 0;
}