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
    printf("from edit_distance, the found LCS is: %d", lcs);
    
    return sa1->size + sa2->size - 2*lcs;
}

void arraycpy(char** dest, char** src, int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
        printf("from arraycpy: %s\n", src[i]);
    }
}

