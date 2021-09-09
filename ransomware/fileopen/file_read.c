#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define targetfile "target.txt"

int main(int argc,char ** argv)
{
    FILE *file;
    file = fopen(targetfile,"rb");

    long lSize;
    fseek(file,0, SEEK_END); 
    lSize = ftell(file); 
    rewind(file); 

    unsigned char * read_msg = malloc(sizeof(char) * (lSize+1));
    memset(read_msg,0,sizeof(char) * (lSize+1));
  
    fread(read_msg, 1, lSize, file);

    printf("%s\n",read_msg);
    printf("%d\n",strlen(read_msg));

    
    fclose(file);

    return 0;
}