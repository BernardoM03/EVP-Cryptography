#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void weak_collision_trial(int trial_num);

int main(int argc, char* argv[]) {

    // Takes in an input of # of trials to run the brute-force hashing script for
    if (argc > 2) return 1;
    int trials = atoi(argv[1]);

    printf("Trials this experiment will run for: %d\n", trials);
    printf("-------------------------------------------\n");

    for (int i = 1; i <= trials; i++) {
        weak_collision_trial(i);
    }


    return 0;
}

unsigned char* hash_message(const char* message) {
    EVP_MD_CTX = *mdctx;
    unsigned int md_len;
    unsigned char full_hash[EVP_MAX_MD_SIZE];

    mdctx = EVP_MD_CTX_new();
    EVP_DIGEST_Init_ex();
}

void weak_collision_trial(int trial_num) {
    //printf("This is Weak Collision Trial run %d\n", trial_num);

    int count_to_break_hash = 0;
    // Write code to see how many attempts it will take a break the hash
    // of the first 24 bits of a hash

    unsigned char target_hash[3];
    unsigned char current_hash[3];

    char target_msg[32];
    char current_msg[32];
}


