#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../include/sync_string.h"

/**
 * Computes the edit distance between two substrings of S.
 *
 * @param S The original string.
 * @param i The starting index of the first substring (inclusive).
 * @param j The starting index of the second substring (inclusive).
 * @param k The ending index of the second substring (exclusive).
 * @return The edit distance between the substrings S[i:j) and S[j:k).
 */
int edit_distance(const char *S, int i, int j, int k) {
    // TODO: Implement the edit distance calculation
    return 4;
}

/**
 * Checks if a string is an ε-synchronization string.
 *
 * @param S The input string to check.
 * @param n The length of the input string S.
 * @param epsilon The epsilon value to use for the check.
 * @return true if the string S is an ε-synchronization string, false otherwise.
 *
 * This function iterates over all possible i, j, and k values to verify that
 * for every 1 ≤ i < j < k ≤ n+1, the edit distance between S[i:j) and S[j:k)
 * is greater than (1 - ε) * (k - i).
 */
bool synchronization_string_checker(const char *S, int n, double epsilon) {
    // Iterate over all possible k, j, and i values
    for (int k = 3; k <= n + 1; k++) {
        for (int j = 2; j < k; j++) {
            for (int i = 1; i < j; i++) {
                // Calculate edit distance for one iteration
                int ed = edit_distance(S, i, j, k);

                int threshold = (1 - epsilon) * (k - i);
                // Check if the edit distance is greater than (1 - epsilon) * (k - i)
                bool flag = ed > threshold;
                
                // Check to see iterations work as expected
                printf("i: %d, j: %d, k: %d, threshold: %d\n", i, j, k, threshold);

                // If the condition is not met, return false
                if (!flag) {
                    return false;
                }
            }
        }
    }
    // If all conditions are met, return true
    return true;
}