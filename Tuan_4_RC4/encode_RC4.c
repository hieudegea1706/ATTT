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
// Giai đoạn 2: Trình tạo giả ngẫu nhiên & Mã hóa (PRGA)
void rc4_prga(unsigned char *S, const unsigned char *plaintext, unsigned char *ciphertext, int text_len) {
    int i = 0, j = 0, k;
    
    for (k = 0; k < text_len; k++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(&S[i], &S[j]);
        
        int t = (S[i] + S[j]) % 256;
        unsigned char keystream_byte = S[t];
        
        // Thực hiện mã hóa: Ciphertext = Plaintext XOR Keystream
        ciphertext[k] = plaintext[k] ^ keystream_byte;
    }
}

int main() {
    // 1. Chuẩn bị dữ liệu
    unsigned char key[] = "SecretKey123"; 
    unsigned char plaintext[] = "cybersecurity";
    int text_len = strlen((char *)plaintext);
    int key_len = strlen((char *)key);
    
    unsigned char S[256];
    unsigned char ciphertext[256];
    unsigned char decryptedtext[256];

    // 2. Quá trình Mã hóa
    rc4_ksa(S, key, key_len);
    rc4_prga(S, plaintext, ciphertext, text_len);

    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext (Hex): ");
    for (int i = 0; i < text_len; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    // 3. Quá trình Giải mã
    // QUAN TRỌNG: Phải thiết lập lại (reset) mảng S bằng hàm KSA trước khi giải mã
    rc4_ksa(S, key, key_len);
    rc4_prga(S, ciphertext, decryptedtext, text_len);
    decryptedtext[text_len] = '\0'; // Thêm ký tự kết thúc chuỗi

    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}