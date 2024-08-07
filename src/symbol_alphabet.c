#include <stdlib.h>
#include <stdio.h>
#include "symbol_alphabet.h"
#include "../include/utility.h"
#include <string.h>



SymbolArray* createSymbolArray(char** symbols, int size) {
    if (symbols == NULL) return NULL;

    SymbolArray* s = malloc(sizeof(SymbolArray));
    if (!s) return NULL;

    // s->symbols = (char**)malloc(size * sizeof(char*));

    s->symbols = symbols;

    // for (int i = 0; i < size; ++i) {
    //     s->symbols[i] = symbols[i];
    //     // printf("from create symbol array: %s\n", s->symbols[i]);
    // }

    s->size = size;
    return s;
}

// This function creates an alphabet and a symbolarray, be sure to deallocate both
SymbolArray* createRandomSymbolArray(Alphabet* a, int symbolArraySize) {
    SymbolArray* s = malloc(sizeof(SymbolArray));

    s->size = symbolArraySize;
    s->symbols = malloc(symbolArraySize * sizeof(char*)); //no need to malloc, just say s->symbols points to a->alphabet[0]...
    
    for (int i = 0; i < symbolArraySize; i++) {
        int randomIndex = rand() % a->size;
        s->symbols[i] = a->alphabet[randomIndex];
        printf("createRandomSymbolArray: %s\n", s->symbols[i]);
    }

    return s;
}


void deleteRandomSymbolArray(SymbolArray* s) {
    if (s) {
        free(s->symbols);
        free(s);
    }
}


void deleteSymbolArray(SymbolArray* s) {
    if (s) {
        free(s);
    }
}


// cannot cover case: bbbc, or bbba, or aaa, or when the alphabet uses duplicate letters
// implement later because it's not clear yet what kind of alphabet i want to generate

// see leetcode problem permutation i and ii

Alphabet* createAlphabet(char** alphabet, int size, char* bot) {
    if (alphabet == NULL) return NULL;

    
    Alphabet* a = malloc(sizeof(Alphabet));
    if (!a) return NULL;

    a->alphabet = alphabet;

    a->size = size;
    a->bot = bot; // not malloc-ing space for bot, because I don't expect bot to take up much memory
}




unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// given abc, return cba bca bac abc acb cab
char** permutations(char* letters) {
    // printf("letters: %s\n", letters);
    int n = strlen(letters);
    int totalPerms = factorial(n);
    // printf("total permutations expected in result: %d\n", totalPerms);
    char** result = (char**)malloc(totalPerms * sizeof(char*));

    if (n == 1) {
        result[0] = strdup(letters);
        // printf("current result instant: %s\n", result[0]);
        return result; // gotta free it tho
    }

    char* temp = strdup(letters); // prevent original letters from being corrupted
    for (int i = 0; i < n; i++) {
        // printf("temp: %s\n", temp); 
        char* first_letter = &temp[0];
        char** perms = permutations(temp + 1);
        
        for (int j = 0; j < factorial(n - 1); j++) { // should be for length of perms..if 1->1, 2->2, 3->6, 4->24
            // Allocate space in result for each permutation
            result[i*(n-1)+j] = (char*)malloc((n + 1) * sizeof(char));
            
            // Copy perms[j] into result[i*(n-1)+j]
            strcpy(result[i*(n-1)+j], perms[j]);
            
            // Append first_letter to result[i*(n-1)+j]
            result[i*(n-1)+j][n - 1] = *first_letter;
            result[i*(n-1)+j][n] = '\0';
            free(perms[j]);
        }
        free(perms);

        rotateRight(temp, n);
    // for (int i = 0; i < factorial(n); i++) {
    //         printf("current result long: %s\n", result[i]);
    // }
    }
    free(temp);
    
    return result;
}

//
char** generateSubsets(char *str, int *count) { 
    int n = strlen(str);
    int totalSubsets = 1 << n; // 2^n
    char **subsets = malloc(totalSubsets * sizeof(char *));
    *count = 0;

    for (int i = 1; i < totalSubsets; i++) { // Start from 1 to skip the empty subset
        char *subset = malloc((n + 1) * sizeof(char));
        int pos = 0;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                subset[pos++] = str[j];
            }
        }
        subset[pos] = '\0';
        subsets[(*count)++] = subset;
    }
    return subsets;
}


// "abc" --> "a", "b", "c", "aa", "bb", "cc", "ab", "ac", "bc", "ba", "ca", "cb", "abc", "bac", "cab", "bca", "cba", "acb" ....
char** createRandomAlphabet(char* letterbank, int size) {
    int count;
    char** subsets = generateSubsets(letterbank, &count);
    int alphabet_size = 0;

    // Allocate memory for the alphabet array
    char** alphabet = malloc(size * sizeof(char*));
    if (alphabet == NULL) {
        // Handle memory allocation failure
        perror("Failed to allocate memory for alphabet");
        return NULL;
    }

    for (int i = 0; i < count && alphabet_size < size; i++) {
        int n = strlen(subsets[i]);
        int permCount = factorial(n);
        char** temp = permutations(subsets[i]);

        // Add elements to the alphabet until capacity is reached
        for (int j = 0; j < permCount && alphabet_size < size; j++) {
            alphabet[alphabet_size] = strdup(temp[j]);
            // printf("here's alphabet size right now, and then the given size: %d, %d, %s\n", alphabet_size, size, alphabet[alphabet_size]);
            alphabet_size++;
        }
        
        for (int j = 0; j < permCount; j++) {
            free(temp[j]);
        }
        free(temp);
    }

    for (int i = 0; i < count; i++) {
        free(subsets[i]);
    }
    free(subsets);

    return alphabet;
}


void deleteAlphabet(Alphabet* a) {
    if (a) {
        // free(a->alphabet);
        free(a);
    }
}

