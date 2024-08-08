#include <stdio.h>
#include <time.h>
#include "../include/sync_string.h"
#include "../include/symbol_alphabet.h"
#include "../include/utility.h"

void sampling(int ss_size, int a_size, int num_strings) {
    struct timespec start, end;
    double elapsed_alphabet = 0, elapsed_string_gen = 0, elapsed_sampling = 0, elapsed_loop = 0;

    // Timing the Alphabet Creation
    clock_gettime(CLOCK_MONOTONIC, &start);
    char** alphabet = createRandomAlphabet("abcdefghijklmnop", a_size);
    Alphabet* a = createAlphabet(alphabet, a_size, "*"); 
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed_alphabet = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Alphabet creation took %f seconds\n", elapsed_alphabet);

    // Timing the entire loop
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < num_strings; i++) {
        // Timing String Generation
        struct timespec string_start, string_end;
        clock_gettime(CLOCK_MONOTONIC, &string_start);
        char** ss_random = random_string(a, ss_size);
        clock_gettime(CLOCK_MONOTONIC, &string_end);
        elapsed_string_gen += (string_end.tv_sec - string_start.tv_sec) + (string_end.tv_nsec - string_start.tv_nsec) / 1e9;

        // Timing Sampling Correction
        struct timespec sample_start, sample_end;
        clock_gettime(CLOCK_MONOTONIC, &sample_start);
        char** ss_corrected = random_sampling(ss_random, ss_size, a, 0.66);
        clock_gettime(CLOCK_MONOTONIC, &sample_end);
        elapsed_sampling += (sample_end.tv_sec - sample_start.tv_sec) + (sample_end.tv_nsec - sample_start.tv_nsec) / 1e9;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed_loop = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("\n");
    printf("+------------------------+--------------------+\n");
    printf("| Stage                  | Time (seconds)     |\n");
    printf("+------------------------+--------------------+\n");
    printf("| Alphabet Creation      | %18.6f |\n", elapsed_alphabet);
    printf("| Total String Generation| %18.6f |\n", elapsed_string_gen);
    printf("| Total Sampling Correction | %18.6f |\n", elapsed_sampling);
    printf("| Entire Loop            | %18.6f |\n", elapsed_loop);
    printf("+------------------------+--------------------+\n");
}

// TODO
// for alphabet sizes from 16 to 2^10
// for sync string lengths from 16 to 2^10
// we want to know if a valid sync string is possible given an alphabet, an alphabet size, and an epsilon. isPossible()

// Reed Solomon Decoder
// message (encode function runs)=> codeword => channel where errors are introduced (make an error making function)=> corrupted codeword => decoded message
// write the full pipeline


int main() {
    struct timespec start, end;
    double total_elapsed;

    clock_gettime(CLOCK_MONOTONIC, &start);

    // Run the sampling function
    int sync_string_size = 5; // Example size, adjust as needed
    int alphabet_size = 10;   // Example size, adjust as needed
    int num_strings = 1000;   // Example number of strings, adjust as needed
    sampling(sync_string_size, alphabet_size, num_strings);

    clock_gettime(CLOCK_MONOTONIC, &end);

    total_elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Total execution took %f seconds\n", total_elapsed);
    return 0;
}
