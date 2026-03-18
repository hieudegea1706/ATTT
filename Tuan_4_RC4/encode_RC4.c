#include <stdio.h>
#include <string.h>

// Hàm hoán vị 2 phần tử
void swap(unsigned char *a, unsigned char *b) {
    unsigned char temp = *a;
    *a = *b;
    *b = temp;
}

// Giai đoạn 1: Lập lịch khóa (Key-Scheduling Algorithm)
void rc4_ksa(unsigned char *S, const unsigned char *key, int key_len) {
    int i, j = 0;
    
    // Khởi tạo mảng S từ 0 đến 255
    for (i = 0; i < 256; i++) {
        S[i] = i;
    }
    
    // Xáo trộn mảng S dựa trên Key
    for (i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % key_len]) % 256;
        swap(&S[i], &S[j]);
    }
}