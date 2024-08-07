#include <stdio.h>
#include <time.h>
#include "../include/sync_string.h"
#include "../include/symbol_alphabet.h"
#include "../include/utility.h"



int main() {
    struct timespec start, end;
    double elapsed;

    clock_gettime(CLOCK_MONOTONIC, &start);

    //take in sync string size, take in alphabet size, take in # strings we want, and run it

    

    clock_gettime(CLOCK_MONOTONIC, &end);

    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("someFunction() took %f seconds to execute\n", elapsed);
    return 0;
}