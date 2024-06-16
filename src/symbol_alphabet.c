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
        printf("%s\n", s->symbols[i]);
    }

    s->size = size;
    return s;
}

void deleteSymbolArray(SymbolArray* s) {
    if (s) {
        free(s->symbols);
        free(s);
    }
}
