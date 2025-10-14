#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void pad_key(const char *word, unsigned char *key) {
    size_t len = strlen(word);
    size_t i;

    for (i = 0; i < len && i < 16; i++) {
        key[i] = (unsigned char)word[i];
    }

    for (; i < 16; i++) {
        key[i] = 0x20;
    }
}

int encrypt(unsigned char *plaintext, int plain_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext) {
    /*
    Use the SSL library here to check if the words in the dictionary are the correct key
    used in generating the ciphertext from the plain text.
    */

    EVP_CIPHER_CTX *ctx = NULL;
    int len = 0;
    int ciphertext_len = 0;
    int final_len = 0;

    // initialize cipher context for ssl EVP lib
    ctx = EVP_CIPHER_CTX_new();

    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);

    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plain_len);

    ciphertext_len = len;

    EVP_EncryptFinal_ex(ctx, ciphertext + len, &final_len);

    ciphertext_len += final_len;

    // free cipher context and return
    EVP_CIPHER_CTX_free(ctx);
    return ciphertext_len;
}

int main() {

    FILE *words_file;
    char word[17];
    unsigned char key[16];
    //printf("Hello World.\n");

    unsigned char plaintext[] = "This is a top secret.";
    int plain_len = 21;
    printf("The size of the plaintext '%s' is %d\n", plaintext, plain_len);

    unsigned char target_ciphertext[] = {
        0x8d, 0x20, 0xe5, 0x05, 0x6a, 0x8d, 0x24, 0xd0,
        0x46, 0x2c, 0xe7, 0x4e, 0x49, 0x04, 0xc1, 0xb5,
        0x13, 0xe1, 0x0d, 0x1d, 0xf4, 0xa2, 0xef, 0x2a,
        0xd4, 0x54, 0x0f, 0xae, 0x1c, 0xa0, 0xaa, 0xf9
    };
    int target_len = sizeof(target_ciphertext);
    printf("The size of the target ciphertext is %d\n", target_len);

    unsigned char iv[16] = {0};
    unsigned char generated_ciphertext[64];
    int generated_len;

    words_file = fopen("words.txt", "r");
    if(words_file == NULL) {
        printf("failed to open words_file");
        return 1;
    }

    while (fgets(word, sizeof(word), words_file) != NULL) {
        word[strcspn(word, "\n")] = 0;

        if (strlen(word) > 0 && strlen(word) < 16) {
            pad_key(word, key);
            generated_len = encrypt(plaintext, plain_len, key, iv, generated_ciphertext);

            if (generated_len == target_len &&
                    memcmp(generated_ciphertext, target_ciphertext, target_len) == 0) {
                printf("Key found: %s\n", word);
                break;
            }
        }
    }

    //printf("Key not found\n");
    fclose(words_file);
    return 0;
}


