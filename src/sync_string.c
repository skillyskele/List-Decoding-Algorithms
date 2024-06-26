#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../include/sync_string.h"
#include "../include/symbol_alphabet.h"
#include "../include/utility.h"




/**
* Finds the longest common subsequence between two SymbolArrays
* @param sa1 First SymbolArray
* @param sa2 Second SymbolArray
* @return Length of the longest common subsequence
*/
int find_LCS(const SymbolArray *sa1, const SymbolArray *sa2) {
    // initialize dp to be all 0
    int rows = sa1->size + 1;
    int cols = sa2->size + 1;
    int dp[rows][cols];
    memset(dp, 0, sizeof(dp));

    for (int i = rows - 2; i >= 0; i--) {
        for (int j = cols - 2; j >= 0; j--) {
            if (sa1->symbols[i] == sa2->symbols[j]) {
                dp[i][j] = 1 + dp[i+1][j+1];
            } else {
                dp[i][j] = max(dp[i][j+1], dp[i+1][j]);
            }
        }
    }
    return dp[0][0];
}

/**
* Calculates the edit distance between two SymbolArrays
* @param sa1 First SymbolArray
* @param sa2 Second SymbolArray
* @return Edit distance between sa1 and sa2
*/
int edit_distance(const SymbolArray *sa1, const SymbolArray *sa2) {
    int lcs = find_LCS(sa1, sa2);
    return sa1->size + sa2->size - 2*lcs;
}

/**
* Generates epsilon-sync strings from a SymbolArray
* @param epsilon Epsilon value
* @param n Size of the SymbolArray
* @param a Alphabet used for generating SymbolArray
*/
void epsilon_sync_string_maker(double epsilon, int n, Alphabet* a) {
    // make the string
    SymbolArray* s = createRandomSymbolArray(a, n); 

    char *str = symbolArrayPrinter(s->symbols, s->size);
    printf("Here's the random symbolarray: %s\n", str);
    
    // check every substring inside s
    // if that substring doesn't pass, we'll call epsilon_sync_string_maker on that substring
    // for now, just output every substring inside s
    for (int len = 1; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            //char* substring = (char**)malloc(sizeof(char*)*(j-i+1)); 
            int strlen = j-i+1;
            char* substring[strlen];
            char *substring_str = symbolArrayPrinter(substring, strlen);
            for (int k = i; k <= j; k++) {
                substring[k-i] = s->symbols[k]; 
            }
            bool valid_sync_str =  synchronization_string_checker(substring, strlen, epsilon);
            printf("%s sync string or not? %d\n", substring_str, valid_sync_str);
            printf("\n");
            free(substring_str);
            if (!valid_sync_str) {
                // do stuff
            }

        }
    }
    deleteSymbolArray(s);
    free(str);
}



/**
* Finds the minimum epsilon for an array of symbol strings
* @param S Array of symbol strings
* @param n Number of strings in S
*/
double minimum_epsilon_finder(char** S, int n) {
    // n must be at least 2
    if (n < 2) {
        return;
    }
    
    // Print the table header
    printf("i\tj\tk\tS[i, j)\t\tS[j, k)\t\ted\tk-i\tmin_epsilon\n");
    printf("----------------------------------------------------------------------\n");

    double min_epsilon = 1.0; // start as maximum value
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
                double epsilon = 1.0 - ((double)ed / (k - i));
                if (epsilon < 0.0) epsilon = 0.0;  // Ensure min_epsilon is within bounds
                if (epsilon > 1.0) epsilon = 1.0;  // Ensure min_epsilon is within bounds

                if (epsilon < min_epsilon) {
                    min_epsilon = epsilon;
                }
                
                char *s1_str = symbolArrayPrinter(s1, j - i);
                char *s2_str = symbolArrayPrinter(s2, k - j);

                // Print the values in a formatted table
                printf("%d\t%d\t%d\t%s\t\t%s\t\t%d\t%d\t%.10f\n", i, j, k, 
                    s1_str, s2_str,
                    ed, k - i, epsilon);

                // Free allocated memory
                deleteSymbolArray(sa1);
                deleteSymbolArray(sa2);
                free(s1_str);
                free(s2_str);
                for (int idx = 0; idx < (j - i); idx++) {
                    free(s1[idx]);
                }
                for (int idx = 0; idx < (k - j); idx++) {
                    free(s2[idx]);
                }
                free(s1);
                free(s2);
            }
        }
    }
    return min_epsilon;
}



bool synchronization_string_checker(char **S, int n, double epsilon) {
    // n must be at least 2
    if (n < 2) {
        return false;
    }

    // Print the table header
    printf("i\tj\tk\tS[i, j)\t\tS[j, k)\t\ted\tthreshold\tflag\n");
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
                    return false;
                }
                arraycpy(s1, S + i, j - i);
                arraycpy(s2, S + j, k - j);

                SymbolArray *sa1 = createSymbolArray(s1, j - i);
                SymbolArray *sa2 = createSymbolArray(s2, k - j);

                // Calculate edit distance for one iteration
                int ed = edit_distance(sa1, sa2);

                // Calculate the threshold
                double threshold = (1 - epsilon) * (k - i);

                // Check if the edit distance is greater than (1 - epsilon) * (k - i)
                bool flag = ed > threshold;

                char *s1_str = symbolArrayPrinter(s1, j - i);
                char *s2_str = symbolArrayPrinter(s2, k - j);

                // Print the values in a formatted table
                printf("%d\t%d\t%d\t%s\t\t%s\t\t%d\t%.10f\t%s\n", i, j, k, 
                    s1_str, s2_str, ed, threshold, flag ? "true" : "false");

                // Free allocated memory
                deleteSymbolArray(sa1);
                deleteSymbolArray(sa2);
                free(s1_str);
                free(s2_str);
                for (int idx = 0; idx < (j - i); idx++) {
                    free(s1[idx]);
                }
                for (int idx = 0; idx < (k - j); idx++) {
                    free(s2[idx]);
                }
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
