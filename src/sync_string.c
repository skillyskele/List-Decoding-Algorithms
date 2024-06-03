#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../include/sync_string.h"


/*
* Finds the maximum integer between two integers
*/
int max(int a, int b) {
    return (a > b) ? a : b;
}


/**
* Finds the longest common subsequence between two strings
* @param s1 is string 1
* @param s1 is string 2
*/
int find_LCS(char *s1, char *s2) {
    // initialize dp to be all 0
    int rows = strlen(s1) + 1;
    int cols = strlen(s2) + 1;
    int dp[rows][cols];
    memset(dp, 0, sizeof(dp));

    // // Print dp at start to see what it is
    // printf("dp array:\n");
    // for (int i = 0; i < rows; i++) {
    //     for (int j = 0; j < cols; j++) {
    //         printf("%d ", dp[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");

    // printf("Rows and Columns: %d, %d\n", rows, cols);
    for (int i = rows - 2; i >= 0; i--) {
        for (int j = cols - 2; j >= 0; j--) {
            // printf("Here's i and j: %d, %d\n", i, j);
            // printf("Currently comparing: %c, %c\n", s1[i], s2[j]);
            if (s1[i] == s2[j]) {
                // printf("%c\n",s1[i]);
                dp[i][j] = 1 + dp[i+1][j+1];
                
            } else {
                dp[i][j] = max(dp[i][j+1], dp[i+1][j]);
            }
            // printf("Here's dp[i][j], %d\n" , dp[i][j]);
        }
    }
    return dp[0][0];
}

/**
 * Computes the edit distance between two substrings of S. 
 * Edit distance is the minimum number of insertions/deletions 
 * required to transform c into c', and is also equal to |c|+|c'|-2*LCS(c,c')
 *
 * @param S The original string.
 * @param i The starting index of the first substring (inclusive).
 * @param j The starting index of the second substring (inclusive).
 * @param k The ending index of the second substring (exclusive).
 * @return The edit distance between the substrings S[i:j) and S[j:k).
 */
int edit_distance(const char *S, int i, int j, int k) {
    // edit distance is the minimum number of insertions/deletions required to transform c into c'
    // also equal to |c|+|c'|-2*LCS(c,c')
    // c = S[i, j)
    // c' = S[j,k)
    const char *c0 = S + i;
    int s1_len = j - i;
    char *s1 = malloc(s1_len+1); // since from i to j-1 inclusive is equal to j - i bytes
    strncpy(s1, c0, s1_len);    
    s1[s1_len] = '\0';

    const char *c1 = S + j;
    int s2_len = k - j;
    char *s2 = malloc(s2_len+1);
    strncpy(s2, c1, s2_len);   
    s2[s2_len] = '\0';

    
    int lcs = find_LCS(s1, s2);
    free(s1);
    free(s2);
    return s1_len + s2_len - 2*lcs;
}

// however, i disagree with the statement in that i think 
// you should be subtracting out ALL matching substrings...they only match if they're in the same exact place of course
// my bad it says longest common subsequence


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