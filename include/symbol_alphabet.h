#ifndef SYMBOL_ALPHABET_H
#define SYMBOL_ALPHABET_H

typedef struct {
    char** symbols;
    int size;
} SymbolArray;

SymbolArray* createSymbolArray(char** symbols, int size);
void deleteSymbolArray(SymbolArray* s);

#endif // SYMBOL_ALPHABET_H
