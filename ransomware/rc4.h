void swap(unsigned char *a, unsigned char *b);
int KSA(char *key, unsigned char *S);
int PRGA(unsigned char * S, char * plaintext, int size, unsigned char * ciphertext);
int RC4(char * key, char * plaintext, int size, unsigned char * ciphertext);