#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Finds the maximum integer between two integers
*/
int max(int a, int b) {
    return (a > b) ? a : b;
}

/**
* Copies an array of symbol strings
* @param dest Destination array
* @param src Source array
* @param n Number of elements to copy
*/
void arraycpy(char** dest, char** src, int n) {
    for (int i = 0; i < n; i++) {
        printf("copying: %s\n", src[i]);
        dest[i] = strdup(src[i]);
    }
}



/**
* Concatenates an array of symbol strings into a single string
* @param s Array of symbol strings
* @param n Number of strings in s
* @return Concatenated string
*/
char* symbolArrayPrinter(char** s, int n) {
    // Calculate the total length needed for the resulting string
    int total_length = 0;
    for (int i = 0; i < n; i++) {
        // printf("from symbolArrayPrinter: %s is %ld long\n", s[i], strlen(s[i]));
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


void rotateRight(char* str, int len) {
    char temp = str[len - 1];
    for (int i = len - 1; i > 0; i--) {
        str[i] = str[i - 1];
    }
    str[0] = temp;
}