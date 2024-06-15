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
int find_LCS(const char *s1, const char *s2) {
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
int edit_distance(const char *s1, int s1_len, const char *s2, int s2_len) {
    // edit distance is the minimum number of insertions/deletions required to transform c into c'
    // also equal to |c|+|c'|-2*LCS(c,c')
    // c = S[i, j)
    // c' = S[j,k)
    

    // printf("Here are strings: %s, %d, %s, %d\n", s1, s1_len, s2, s2_len);
    int lcs = find_LCS(s1, s2);
    
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
    
    // n must be at least 2
    if (n < 2) {
    return false;
    }
    // Iterate over all possible k, j, and i values
    // In this loop, i starts at 0, instead of 1, because in C, 0 means the first letter of a string, not 1
    for (int k = 2; k <= n + 1; k++) {
        for (int j = 1; j < k; j++) {
            for (int i = 0; i < j; i++) {

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

                // Calculate edit distance for one iteration
                int ed = edit_distance(s1, s1_len, s2, s2_len);

                double threshold = (1 - epsilon) * (k - i);
                // Check if the edit distance is greater than (1 - epsilon) * (k - i)
                bool flag = ed > threshold;
                
                // Check to see iterations work as expected
                printf("i: %d, j: %d, k: %d, ed: %d, threshold: %f\n", i, j, k, ed, threshold);

                free(s1);
                free(s2);   

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


void minimum_epsilon_finder(const char *S, int n) {
    // n must be at least 2
    if (n < 2) {
        return;
    }

    // Print the table header
    printf("i\tj\tk\tS[i, j)\t\tS[j, k)\t\ted\tk-i\tmin_epsilon\n");
    printf("----------------------------------------------------------------------\n");

    // Iterate over all possible k, j, and i values
    for (int k = 2; k <= n; k++) {
        for (int j = 1; j < k; j++) {
            for (int i = 0; i < j; i++) {

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

                // Calculate edit distance for one iteration
                int ed = edit_distance(s1, s1_len, s2, s2_len);

                // Check for allocation failure
                if (!s1 || !s2) {
                    fprintf(stderr, "Memory allocation failed\n");
                    return;
                }

                // Calculate the minimum epsilon
                double min_epsilon = 1.0 - ((double)ed / (k - i));
                if (min_epsilon < 0.0) min_epsilon = 0.0;  // Ensure min_epsilon is within bounds
                if (min_epsilon > 1.0) min_epsilon = 1.0;  // Ensure min_epsilon is within bounds

                // Print the values in a formatted table
                printf("%d\t%d\t%d\t%s\t\t%s\t\t%d\t%d\t%.10f\n", i, j, k, s1, s2, ed, k - i, min_epsilon);

                // Free the allocated memory
                free(s1);
                free(s2);
            }
        }
    }
}


// should append 'bot' to the smaller string
double compute_rsd(const char *S, const char *S_prime) {
    int len_S = strlen(S);
    int len_S_prime = strlen(S_prime);
    // printf("length of S: %d length of S': %d\n", len_S, len_S_prime);
    int max_len = (len_S > len_S_prime) ? len_S : len_S_prime;
    double max_rsd = 0.0;

    // Print table headers
    printf("%-6s | %-15s | %-15s | %-3s | %-3s | %-3s | %-10s | %-10s | %-6s\n", 
           "k", "Suffix S", "Suffix S'", "i", "j", "k", "Edit Dist", "2k", "RSD");
    printf("----------------------------------------------------------------------\n");

    for (int k = 1; k <= max_len; k++) {
        // Create suffixes for S
        char *suffix_S = (char *)malloc((k + 1) * sizeof(char));
        if (suffix_S == NULL) {
            perror("malloc failed");
            exit(EXIT_FAILURE);
        }

        if (len_S - k >= 0) {
            strncpy(suffix_S, S + len_S - k, k);
            suffix_S[k] = '\0';
        } else {
            strcpy(suffix_S, S); //maybe i need to null terminate
        }

        // Create suffixes for S'
        char *suffix_S_prime = (char *)malloc((k + 1) * sizeof(char));
        if (suffix_S_prime == NULL) {
            free(suffix_S);
            perror("malloc failed");
            exit(EXIT_FAILURE);
        }

        if (len_S_prime - k >= 0) {
            strncpy(suffix_S_prime, S_prime + len_S_prime - k, k);
            suffix_S_prime[k] = '\0';
        } else {
            strcpy(suffix_S_prime, S_prime);
            // printf("Here's substring: %s, and ending: %c and length: %d\n", suffix_S_prime, suffix_S_prime[strlen(suffix_S_prime)], strlen(suffix_S_prime));
        }

        int ed = edit_distance(suffix_S, strlen(suffix_S), suffix_S_prime, strlen(suffix_S_prime));
        double rsd = (double)ed / (2 * k);

        // Print the current row in the table
        printf("%-6d | %-15s | %-15s | %-3d | %-3d | %-3d | %-10d | %-10d | %-6.4f\n", 
               k, suffix_S, suffix_S_prime, len_S - k, len_S_prime - k, k, ed, 2 * k, rsd);

        if (rsd > max_rsd) {
            max_rsd = rsd;
        }

        // Free dynamically allocated memory
        free(suffix_S);
        free(suffix_S_prime);

        // if (max_rsd == 1) {
        //     return max_rsd;
        // }
    }

    return max_rsd;
}