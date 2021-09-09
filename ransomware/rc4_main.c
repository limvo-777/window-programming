#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rc4.h"

int main(int argc, char ** argv){
    
    unsigned char * key = "abcdefgh\0"; // "\0" 문자열 종료를 알리는 문자
    unsigned char * plaintext = "hello\0";
    unsigned char * ciphertext = malloc(sizeof(char) * strlen(plaintext));
    unsigned char * decryptext = malloc(sizeof(char) * strlen(plaintext));
    memset(ciphertext, 0, sizeof(char) * strlen(plaintext)); // buffer의 cipher text를 plain text 길이만큼 0으로 set
    memset(decryptext, 0, sizeof(char) * strlen(plaintext));
    printf("%d\n",strlen(ciphertext));
    printf("*** ENCRYPT ***\n");
    RC4(key, plaintext, strlen(plaintext),ciphertext);
    for(int i=0, len=strlen(plaintext); i<len; i++ ) // cipher text에 null byte가 들어가면 strlen 중단됨
        printf("%02hhx",ciphertext[i]); // x : 4byte, hx : 2byte, hhx: 1byte
    printf("\n");

    printf("*** DECRYPT ***\n");
    RC4(key, ciphertext, strlen(plaintext),decryptext);
    for(int i=0, len=strlen(plaintext); i<len; i++ ) // cipher text에 null byte가 들어가면 strlen 중단됨
        printf("%02hhx",decryptext[i]);
    printf("\n%s\n",decryptext);
    printf("\n");
    printf("%d\n",strlen(plaintext));
    printf("%d\n",strlen(ciphertext));
    printf("\n");

    return 0;
}