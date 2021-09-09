#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rc4.h"

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

    unsigned char * key = "abcdefghi\0"; // "\0" 문자열 종료를 알리는 문자
    unsigned char * plaintext = read_msg;
    //unsigned char * dummy = "\0";
    //strcat(plaintext,dummy);
    unsigned char * ciphertext = malloc(sizeof(char) * (lSize+1));
    unsigned char * decryptext = malloc(sizeof(char) * (lSize+1));
    memset(ciphertext, 0, sizeof(char) * (lSize+1)); // buffer의 cipher text를 plain text 길이만큼 0으로 set
    memset(decryptext, 0, sizeof(char) * (lSize+1));
    printf("%d\n",strlen(ciphertext));

    printf("*** ENCRYPT ***\n");
    RC4(key, plaintext, strlen(plaintext),ciphertext);
    printf("%d\n",strlen(plaintext));
    for(int i=0, len=strlen(plaintext); i<len; i++ ) // cipher text에 null byte가 들어가면 strlen 중단됨
        printf("%02hhx",ciphertext[i]); // x : 4byte, hx : 2byte, hhx: 1byte
    printf("\n");

    FILE *file1;
    file1 = fopen(targetfile,"wb");

    unsigned char * write_msg = ciphertext;
    fwrite(write_msg, strlen(write_msg), 1, file1);

    fclose(file1);

    rename(targetfile,"encrypted.zxc");
    // printf("*** DECRYPT ***\n");
    // RC4(key, ciphertext, strlen(plaintext),decryptext);
    // for(int i=0, len=strlen(plaintext); i<len; i++ ) // cipher text에 null byte가 들어가면 strlen 중단됨
    //     printf("%02hhx",decryptext[i]);
    // printf("\n%s\n",decryptext);

    // printf("\n");
    // printf("%d\n",strlen(plaintext));
    // printf("%d\n",strlen(ciphertext));
    // printf("\n");


    return 0;
}