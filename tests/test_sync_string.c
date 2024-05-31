#include <stdio.h>
#include <stdbool.h>
#include "../include/sync_string.h"

int main() {
    // Test synchronization strings
    const char* sync_string_1 = "123456789x";
    const char* sync_string_2 = "abcdefghij";

    // Test parameters
    int n = 10; // Length of the synchronization strings
    double epsilon = 0.1; // Epsilon value for the check

    synchronization_string_checker(sync_string_1, n, epsilon);

    synchronization_string_checker(sync_string_2, n, epsilon);

    // Test synchronization_string_checker function
    // printf("Testing synchronization_string_checker function:\n");
    // printf("Synchronization string 1: %s\n", sync_string_1);
    // printf("Result: %s\n", synchronization_string_checker(sync_string_1, n, epsilon) ? "true" : "false");

    // printf("Synchronization string 2: %s\n", sync_string_2);
    // printf("Result: %s\n", synchronization_string_checker(sync_string_2, n, epsilon) ? "true" : "false");

    return 0;
}
