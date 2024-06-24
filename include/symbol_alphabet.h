#ifndef SYMBOL_ALPHABET_H
#define SYMBOL_ALPHABET_H

typedef struct {
    char** symbols;
    int size;
} SymbolArray;

SymbolArray* createSymbolArray(char** symbols, int size);
void deleteSymbolArray(SymbolArray* s);

// an alphabet should be a hash table, but for now, i'll implement it as a regular array, and search it with linear search
typedef struct {
    char** alphabet;
    int size;
    char* bot;  // a bot is the character that should never be used in the alphabet
} Alphabet;

// create an alphabet based on a given letterbank, such as "abc" -> a, b, c, ab, ac, bc...
Alphabet* createAlphabet(char** alphabet, int capacity, char* bot);
void deleteAlphabet(Alphabet* a);

SymbolArray* createRandomSymbolArray(Alphabet* a, int symbolArraySize);

SymbolArray* createEmptySymbolArray(int size);


char** permutations(char* letters);



#endif // SYMBOL_ALPHABET_H
