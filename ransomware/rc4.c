#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 256

void swap(unsigned char *a, unsigned char *b){
    int tmp = *a;
    *a = *b;
    *b =tmp;
}

int KSA(char *key, unsigned char *S) //key scheduling
{
    //S배열 초기화
    for(int i=0; i<N; i++){
        S[i] = i;
    }

    int len = strlen(key);
    int j =0;

    for(int i=0;i<N;i++){
        // j 계산, key = "test"
        j = (j + S[i] + key[i % len]) % N;

        //swap
        swap(&S[i],&S[j]);
    }

    return 0;

}

int PRGA(unsigned char * S, char * plaintext, int size, unsigned char * ciphertext)
{
    int i = 0;
    int j = 0;

    // 0 to length of plaintext
    for(int n=0;n<size;n++) //plaintext의 길이 (n)
    {
        i = (i+1) % N;
        j = (j+S[i]) % N;
        swap(&S[i],&S[j]);

        int t = (S[i]+S[j]) % N;
        int key_str = S[t];

        ciphertext[n] = key_str ^ plaintext[n];
    }

    return 0;
}

// RC4 암호화 함수
int RC4(char * key, char * plaintext, int size, unsigned char * ciphertext)
{
    unsigned char S[N];
    KSA(key, S);

    PRGA(S, plaintext, size, ciphertext);
    
    return 0;
}