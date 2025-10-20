#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void weak_collision_trial(int trial_num);
void strong_collision_trial(int trial_num);

int main(int argc, char* argv[]) {

    // Takes in an input of # of trials to run the brute-force hashing script for
    if (argc > 2) return 1;
    int trials = atoi(argv[1]);

    printf("Trials this experiment will run for: %d\n", trials);
    printf("-------------------------------------------\n");

    for (int i = 1; i <= trials; i++) {
        weak_collision_trial(i);
        strong_collision_trial(i);
    }


    return 0;
}

void hash_message(const char* message, unsigned char *out_hash) {
    EVP_MD_CTX *mdctx;
    unsigned int md_len;
    unsigned char full_hash[EVP_MAX_MD_SIZE];

    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(mdctx, message, strlen(message));
    EVP_DigestFinal_ex(mdctx, full_hash, &md_len);
    EVP_MD_CTX_free(mdctx);

    memcpy(out_hash, full_hash, 3);
}

void print_hash(const char *label, const unsigned char *hash) {
    printf("%s: ", label);
    for (int i = 0; i < 3; i++) {
        // %02x prints the character as a two-digit hexadecimal, zero-padded
        printf("%02x", hash[i]);
    }
}

void strong_collision_trial(int trial_num){
    const unsigned long HASH_SPACE_SIZE = 1UL << (3 * 8); // 2^24
    static char *seen_hashes = NULL;
    if (seen_hashes == NULL) {
        seen_hashes = calloc(HASH_SPACE_SIZE, sizeof(char)); // 16MB alloc
     } else {
        memset(seen_hashes, 0, HASH_SPACE_SIZE);
     }

    long long count_to_break_hash = 0;
    unsigned char current_hash[3];
    char current_msg[32];
    unsigned long hash_key;

    do {
        sprintf(current_msg, "strong_search_M_%lld_%d", count_to_break_hash++, trial_num);
        hash_message(current_msg, current_hash);

        hash_key = (unsigned long)current_hash[0] << 16;
        hash_key |=  (unsigned long)current_hash[1] << 8;
        hash_key |=  (unsigned long)current_hash[2];

        if(seen_hashes[hash_key] == 1) break;

        seen_hashes[hash_key] = 1;

    } while(count_to_break_hash < HASH_SPACE_SIZE);

    printf("Strong Collision Trial %d, Attempts: %d\n", trial_num, count_to_break_hash);

}

void weak_collision_trial(int trial_num) {
    //printf("This is Weak Collision Trial run %d\n", trial_num);

    long long count_to_break_hash = 0;
    // Write code to see how many attempts it will take a break the hash
    // of the first 24 bits of a hash
    // 3 = 24 bits
    unsigned char target_hash[3];
    unsigned char current_hash[3];

    char target_msg[32];
    char current_msg[32];

    sprintf(target_msg, "fixed_target_M1_%d", trial_num);
    hash_message(target_msg, target_hash);

    do {
        sprintf(current_msg, "search_m2_try_%lld_%d", count_to_break_hash++, trial_num);
        hash_message(current_msg, current_hash);
        /*printf("Count: %lld, ", count_to_break_hash);
        iprint_hash("Target Hash", target_hash);
        printf(",  ");
        print_hash("Current Hash", current_hash);
        printf("\n");*/

    } while (memcmp(target_hash, current_hash, 3) != 0);

    printf("Weak Collision Trial %d, Attempts: %d\n", trial_num, count_to_break_hash);
}


