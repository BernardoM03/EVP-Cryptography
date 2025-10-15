#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void trial_run(int trial_num);

int main(int argc, char* argv[]) {

    // Takes in an input of # of trials to run the brute-force hashing script for
    if (argc > 2) return 1;
    int trials = atoi(argv[1]);

    printf("Trials this experiment will run for: %d\n", trials);
    printf("-------------------------------------------\n");

    for (int i = 1; i <= trials; i++) {
        trial_run(i);
    }


    return 0;
}

void trial_run(int trial_num) {
    printf("This is trial run %d\n", trial_num);

    int count_to_break_hash = 0;
    // Write code to see how many attempts it will take a break the hash
    // of the first 24 bits of a hash
}
