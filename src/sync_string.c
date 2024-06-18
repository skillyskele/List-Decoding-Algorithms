#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../include/sync_string.h"
#include "../include/symbol_alphabet.h"
#include <stdbool.h>


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
int find_LCS(const SymbolArray *sa1, const SymbolArray *sa2) {
    // initialize dp to be all 0
    int rows = sa1->size + 1;
    int cols = sa2->size + 1;
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
            if (sa1->symbols[i] == sa2->symbols[j]) {
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

int edit_distance(const SymbolArray *sa1, const SymbolArray *sa2) {
    // edit distance is the minimum number of insertions/deletions required to transform c into c'
    // also equal to |c|+|c'|-2*LCS(c,c')
    // c = S[i, j)
    // c' = S[j,k)
    

    // printf("Here are strings: %s, %d, %s, %d\n", s1, s1_len, s2, s2_len);
    int lcs = find_LCS(sa1, sa2);
    // printf("from edit_distance, the found LCS is: %d", lcs);
    
    return sa1->size + sa2->size - 2*lcs;
}

void arraycpy(char** dest, char** src, int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
        //printf("from arraycpy: %s\n", src[i]);
    }
}

void minimum_epsilon_finder(char** S, int n) {
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

                // Allocate memory and copy substrings
                char** s1 = malloc((j - i) * sizeof(char*));
                char** s2 = malloc((k - j) * sizeof(char*));
                if (!s1 || !s2) {
                    fprintf(stderr, "Memory allocation failed\n");
                    return;
                }
                arraycpy(s1, S + i, j - i);
                arraycpy(s2, S + j, k - j);

                SymbolArray *sa1 = createSymbolArray(s1, j - i);
                SymbolArray *sa2 = createSymbolArray(s2, k - j);

                // Calculate edit distance for one iteration
                int ed = edit_distance(sa1, sa2);

                // Calculate the minimum epsilon
                double min_epsilon = 1.0 - ((double)ed / (k - i));
                if (min_epsilon < 0.0) min_epsilon = 0.0;  // Ensure min_epsilon is within bounds
                if (min_epsilon > 1.0) min_epsilon = 1.0;  // Ensure min_epsilon is within bounds
                
                char *s1_str = symbolArrayPrinter(s1, j - i);
                char *s2_str = symbolArrayPrinter(s2, k - j);
                // Print the values in a formatted table
                printf("%d\t%d\t%d\t%s\t\t%s\t\t%d\t%d\t%.10f\n", i, j, k, 
                    s1_str, s2_str,
                    ed, k - i, min_epsilon);



                // Free the allocated memory
                deleteSymbolArray(sa1);
                deleteSymbolArray(sa2);
                free(s1_str);
                free(s2_str);
                free(s1);
                free(s2);
            }
        }
    }
}


// Function to concatenate an array of symbol strings into a single string
char* symbolArrayPrinter(char** s, int n) {
    // Calculate the total length needed for the resulting string
    int total_length = 0;
    for (int i = 0; i < n; i++) {
        total_length += strlen(s[i]);
    }

    // Allocate memory for the resulting string (+1 for the null terminator)
    char* result = malloc((total_length + 1) * sizeof(char));
    if (!result) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // Concatenate the symbols into the result string
    result[0] = '\0';  // Initialize the result string with an empty string
    for (int i = 0; i < n; i++) {
        strcat(result, s[i]);  // Concatenate each symbol string
    }

    return result;
}