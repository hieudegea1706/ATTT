#include <stdio.h>
#include <string.h>


void swap(unsigned char *a, unsigned char *b) {
    unsigned char temp = *a;
    *a = *b;
    *b = temp;
}


void rc4_ksa(unsigned char *S, const unsigned char *key, int key_len) {
    int i, j = 0;
    
    for (i = 0; i < 256; i++) {
        S[i] = i;
    }
    
    
    for (i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % key_len]) % 256;
        swap(&S[i], &S[j]);
    }
}

void rc4_prga(unsigned char *S, const unsigned char *plaintext, unsigned char *ciphertext, int text_len) {
    int i = 0, j = 0, k;
    
    for (k = 0; k < text_len; k++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(&S[i], &S[j]);
        
        int t = (S[i] + S[j]) % 256;
        unsigned char keystream_byte = S[t];
        
        
        ciphertext[k] = plaintext[k] ^ keystream_byte;
    }
}

int main() {
    
    unsigned char key[] = "SecretKey123"; 
    unsigned char plaintext[] = "cybersecurity";
    int text_len = strlen((char *)plaintext);
    int key_len = strlen((char *)key);
    
    unsigned char S[256];
    unsigned char ciphertext[256];
    unsigned char decryptedtext[256];

    
    rc4_ksa(S, key, key_len);
    rc4_prga(S, plaintext, ciphertext, text_len);

    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext (Hex): ");
    for (int i = 0; i < text_len; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    
    rc4_ksa(S, key, key_len);
    rc4_prga(S, ciphertext, decryptedtext, text_len);
    decryptedtext[text_len] = '\0'; 

    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}