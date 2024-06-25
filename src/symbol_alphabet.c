#include <stdlib.h>
#include <stdio.h>
#include "symbol_alphabet.h"
#include "../include/utility.h"
#include <string.h>



SymbolArray* createSymbolArray(char** symbols, int size) {
    if (symbols == NULL) return NULL;

    SymbolArray* s = malloc(sizeof(SymbolArray));
    if (!s) return NULL;

    s->symbols = (char**)malloc(size * sizeof(char*));
    if (!s->symbols) {
        free(s);
        return NULL;
    }

    for (int i = 0; i < size; ++i) {
        s->symbols[i] = symbols[i];
        // printf("from create symbol array: %s\n", s->symbols[i]);
    }

    s->size = size;
    return s;
}

SymbolArray* createEmptySymbolArray(int size) {
    SymbolArray* s = malloc(sizeof(SymbolArray));
    if (!s) return NULL;

    s->symbols = (char**)malloc(size * sizeof(char*));
    if (!s->symbols) {
        free(s);
        return NULL;
    }
    s->size = size;
    return s;
}

void deleteSymbolArray(SymbolArray* s) {
    if (s) {
        // for (int i = 0; i < s->size; i++) {
        //     free(s->symbols[i]);
        // }
        free(s->symbols);
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

    a->alphabet = (char**)malloc(size * sizeof(char*));
    if (!a->alphabet) {
        free(a);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        a->alphabet[i] = alphabet[i];
    }

    a->size = size;
    a->bot = bot; // not malloc-ing space for bot, because I don't expect bot to take up much memory
}

// This function creates an alphabet and a symbolarray, be sure to deallocate both
SymbolArray* createRandomSymbolArray(Alphabet* a, int symbolArraySize) {
    SymbolArray* s = malloc(sizeof(SymbolArray));
    if (!s) return NULL;

    s->symbols = malloc(symbolArraySize * sizeof(char*));
    if (!s->symbols) {
        free(s);
        return NULL;
    }

    s->size = symbolArraySize;

    for (int i = 0; i < symbolArraySize; i++) {
        int randomIndex = rand() % a->size;
        s->symbols[i] = a->alphabet[randomIndex];
    }

    return s;

}

// first you call combinations, then you call permutations. 
// "abc" --> "a", "b", "c", "ab", "ac", "bc", "ba", "ca", "cb", "abc", "bac", "cab", "bca", "cba", "acb"
char** createRandomAlphabetI(char* letterbank, int size, char* bot) { // go thru every substring, like a, b, c, ab, bc, abc,  and then call permutation on it? wrong. it's not able to do "ac" and "ca"
    char* temp;
    char** alphabet;
    for (int i =  0; i < strlen(letterbank); i++) {
        // loop thru abc, strcat to temp and add temp to the growing alphabet
    }

}

char** combinations(char* letterbank) {
    int n = strlen(letterbank);
}

unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

char** permutations(char* letters) {
    // printf("letters: %s\n", letters);
    int n = strlen(letters);
    int totalPerms = factorial(n);
    printf("total permutations expected in result: %d\n", totalPerms);
    char** result = (char**)malloc(totalPerms * sizeof(char*));

    if (n == 1) {
        result[0] = strdup(letters);
        printf("current result instant: %s\n", result[0]);
        return result; // gotta free it tho
    }

    char* temp = strdup(letters); // prevent original letters from being corrupted
    for (int i = 0; i < n; i++) {
        // printf("temp: %s\n", temp); 
        char* first_letter = &temp[0];
        char** perms = permutations(temp + 1);
        
        for (int j = 0; j < factorial(n - 1); j++) { // should be for length of perms..if 1->1, 2->2, 3->6, 4->24
            char* perm = (char*)malloc((n + 1) * sizeof(char));
            strcpy(perm, perms[j]);
            perm[n - 1] = *first_letter; 
            perm[n] = '\0'; 
            printf("current n-1: %d, index: %d, i: %d, j: %d\t appending first word and perms[j] to result: %s\n", n-1, i * (n - 1) + j, i, j, perm); //this is wrong because it writes over what i have
            result[i*(n-1)+j] = perm; 
            // printf("index: %d\n", index);
            free(perm);
        }
        free(perms); // free it in a loop later

        rotateRight(temp, n);
    for (int i = 0; i < factorial(n); i++) {
            printf("current result long: %s\n", result[i]);
    }
    }
    free(temp);
    
    return result;
}

// char** permutations(char* letters) {
//     // printf("letters: %s\n", letters);
//     int n = strlen(letters);
//     int totalPerms = factorial(n);
//     char** result = (char**)malloc(totalPerms * sizeof(char*));
//     int index = 0;

//     char* temp = strdup(letters);
//     for (int i = 0; i < n; i++) {
//         char **perms = permutations(temp+1);
//         for (int j = 0; j < factorial(n-1); j++) {
//             result[index] = "some value"; 
//             index++; 
//             printf("index: %d\n", index);
//         }
        
//     }
    
//     return result;
// }


// "abc" --> "a", "b", "c", "aa", "bb", "cc", "ab", "ac", "bc", "ba", "ca", "cb", "abc", "bac", "cab", "bca", "cba", "acb" ....
char** createRandomAlphabetII(char * letterbank, int size, char* bot) {
    //

}

void deleteAlphabet(Alphabet* a) {
    if (a) {
        free(a->alphabet);
        free(a);
    }
}

