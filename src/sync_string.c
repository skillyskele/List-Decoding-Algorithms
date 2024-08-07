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
    int rows = sa1->size + 1;
    int cols = sa2->size + 1;
    int dp[rows][cols];
    memset(dp, 0, sizeof(dp)); 
    // printf("yo here are rows and cols: %d, %d\n", rows, cols);

    for (int i = rows - 2; i >= 0; i--) {
        for (int j = cols - 2; j >= 0; j--) {
            // printf("comparing s1 and s2: %s, %s\n", sa1->symbols[i], sa2->symbols[j]);
            if (strcmp(sa1->symbols[i], sa2->symbols[j])==0) { //should be strcmp, comparing pointers, not memory
                // printf("here!\n");
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
* corrects a string into a valid epsilon-sync strings by replacing invalid substrings with randomly generated substrings until the whole thing works
* @param epsilon desired epsilon value
* @param n size of the desired sync string
* @param a Alphabet used for generating sync string
*/
char** random_sampling(char** s, int n, Alphabet* a, double epsilon) {
    bool replacement_made;
    do {
        replacement_made = false;
        for (int len = 1; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                int strlen = j - i + 1;
                char** substring = s + i;
                bool valid_sync_str = synchronization_string_checker(substring, strlen, epsilon);
                char *substring_str = symbolArrayPrinter(substring, strlen);
                printf("substring under test: %s and its length: %d\n", substring_str, strlen);
                printf("%s sync string or not? %d\n", substring_str, valid_sync_str);
                free(substring_str);
                if (!valid_sync_str) {
                    char** new_str = random_string(a, strlen);
                    char* temp = symbolArrayPrinter(new_str, strlen);
                    printf("new random string: %s, %d long\n", temp, strlen);
                    free(temp);
                    // strlen slots from s+i onward get replaced by this random string
                    for (int k = 0; k < strlen; k++) { //remember, s is in the heap
                        s[k + i] = new_str[k];
                    }
                    char* t = symbolArrayPrinter(s, n);
                    printf("replaced string: %s, %d long\n", t, strlen);
                    free(t);
                    free(new_str);
                    replacement_made = true;
                    break;
                }
            }
            if (replacement_made) {
                break;
            }
        }
    } while (replacement_made);
    return s; //or maybe return like, "final_s"
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

                char **s1 = S + i;
                char **s2 = S + j;
                int len1 = j - i;
                int len2 = k - j;

                SymbolArray *sa1 = createSymbolArray(s1, len1);
                SymbolArray *sa2 = createSymbolArray(s2, len2);

                // Calculate edit distance for one iteration
                int ed = edit_distance(sa1, sa2);

                // Calculate the minimum epsilon
                double epsilon = 1.0 - ((double)ed / (k - i));
                if (epsilon < 0.0) epsilon = 0.0;  // Ensure min_epsilon is within bounds
                if (epsilon > 1.0) epsilon = 1.0;  // Ensure min_epsilon is within bounds

                if (epsilon < min_epsilon) {
                    min_epsilon = epsilon;
                }
                
                char *s1_str = symbolArrayPrinter(s1, len1);
                char *s2_str = symbolArrayPrinter(s2, len2);

                // Print the values in a formatted table
                printf("%d\t%d\t%d\t%s\t\t%s\t\t%d\t%d\t%.10f\n", i, j, k, 
                    s1_str, s2_str,
                    ed, k - i, epsilon);

                // Free allocated memory
                deleteSymbolArray(sa1);
                deleteSymbolArray(sa2);
                free(s1_str);
                free(s2_str);
            }
        }
    }
    return min_epsilon;
}



bool synchronization_string_checker(char **S, int n, double epsilon) {
    // n must be at least 2
    if (n < 2) {
        printf("just retuned true since n < 2!\n");
        return true;
    }

    // Print the table header
    printf("i\tj\tk\tS[i, j)\t\tS[j, k)\t\ted\tthreshold\tflag\n");
    printf("----------------------------------------------------------------------\n");

    // Iterate over all possible k, j, and i values
    for (int k = 2; k <= n; k++) {
        for (int j = 1; j < k; j++) {
            for (int i = 0; i < j; i++) {
                char **s1 = S + i;
                char **s2 = S + j;
                int len1 = j - i;
                int len2 = k - j;

                // to be honest, we don't need to createSymbolArray, 
                // we should just pass s1 and s2 directly into 

                SymbolArray *sa1 = createSymbolArray(s1, len1);
                SymbolArray *sa2 = createSymbolArray(s2, len2);

                // Calculate edit distance for one iteration
                int ed = edit_distance(sa1, sa2);

                // Calculate the threshold
                double threshold = (1 - epsilon) * (k - i);

                // Check if the edit distance is greater than (1 - epsilon) * (k - i)
                bool flag = ed > threshold;

                char *s1_str = symbolArrayPrinter(s1, len1);
                char *s2_str = symbolArrayPrinter(s2, len2);

                // Print the values in a formatted table
                printf("%d\t%d\t%d\t%s\t\t%s\t\t%d\t%.10f\t%s\n", i, j, k, 
                    s1_str, s2_str, ed, threshold, flag ? "true" : "false");

                // Free allocated memory
                deleteSymbolArray(sa1);
                deleteSymbolArray(sa2);
                free(s1_str);
                free(s2_str);

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
