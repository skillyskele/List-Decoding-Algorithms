#include <stdlib.h>
#include <stdio.h>
#include "symbol_alphabet.h"


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

Alphabet* createAlphabet(char* letterbank, int capacity, char* bot) {
  
}

void deleteAlphabet(Alphabet* a) {
    if (a) {
        if (a->alphabet) {
            for (int i = 0; i < a->capacity; i++) {
                free(a->alphabet[i]);
            }
            free(a->alphabet);
        }
        free(a->bot);
        free(a);
    }
}

