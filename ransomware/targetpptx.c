#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rc4.h"

// #define targetfile "target.pptx"


int main(int argc,char ** argv)
{
    char* targetfile =  "target.pptx";
    int ans = 0;
    printf("------ encrypt (1) , decrypt(2) : ");
    scanf("%d", &ans);

    if (ans==2){
        targetfile = "encrypted.zxc";
    }else{
        targetfile = "target.pptx";
    }

    //file open
    FILE *file;
    file = fopen(targetfile,"rb");

    long lSize;
    fseek(file,0, SEEK_END); 
    lSize = ftell(file); 
    rewind(file); 

    unsigned char * read_msg = malloc(sizeof(char) * (lSize+1));
    memset(read_msg,0,sizeof(char) * (lSize+1));
  
    fread(read_msg, 1, lSize, file);
    
    fclose(file);

    //encrypt conf
    unsigned char * key = "abcdefghi\0"; 
    unsigned char * plaintext = read_msg;
    unsigned char * ciphertext = malloc(sizeof(char) * (lSize+1));
    unsigned char * decryptext = malloc(sizeof(char) * (lSize+1));
    memset(ciphertext, 0, sizeof(char) * (lSize+1)); 
    memset(decryptext, 0, sizeof(char) * (lSize+1));

    //encrypt & decrypt
    RC4(key, plaintext, lSize, ciphertext);
    if (ans==2){    
        printf("*** DECRYPT ***\n");
    }else{
        printf("*** ENCRYPT ***\n");
    }
    printf("%d\n",strlen(plaintext));
   
    printf("original : ");
    for(int i=0, len=strlen(plaintext); i<len; i++ ) 
        printf("%02hhx",ciphertext[i]); 
    printf("\n");
    printf("changed : %s\n",ciphertext);

    // fileopen
    file = fopen(targetfile,"wb");
    fwrite(ciphertext, lSize, 1, file);
    fclose(file);


    //rename
    if (ans==2){
        rename(targetfile,"decrypted.pptx");
    }else{
        rename(targetfile,"encrypted.zxc");
    }

    rename(targetfile,"encrypted.zxc");
  

    return 0;
}