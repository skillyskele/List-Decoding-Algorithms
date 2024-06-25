#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "../include/symbol_alphabet.h"
#include "../include/sync_string.h"
#include "../include/utility.h"
#include "unity.h"

void setUp(void) {
    srand(time(NULL));
}

void tearDown(void) {
}

void test_symbol_constructor() {
    char* symbols[] = {"1", "symbol2", "symbol3"};
    int size = 3;
    SymbolArray* s = createSymbolArray(symbols, size);
    TEST_ASSERT_NOT_NULL(s);
    TEST_ASSERT_EQUAL(size, s->size);
    for (int i = 0; i < size; i++) {
        TEST_ASSERT_EQUAL_STRING(symbols[i], s->symbols[i]);
    }
    deleteSymbolArray(s);
}

void test_alphabet_constructor() {
    char* a1[] = {"a", "b", "c", "d", "e"};
    int size = 5;
    char* bot =  "~";
    Alphabet* alpha1 = createAlphabet(a1, 5, bot);
    for (int i = 0; i < size; i++) {
        printf("%s\n", alpha1->alphabet[i]);
    }

    char** a2 = malloc((5)*sizeof(char*));
    arraycpy(a2, a1, 5);

    Alphabet* alpha2 = createAlphabet(a2, 5, bot);
    for (int i = 0; i < size; i++) {
        printf("%s\n", alpha2->alphabet[i]);
    }

    free(a2);
    deleteAlphabet(alpha1);
    deleteAlphabet(alpha2);

}

void test_createRandomSymbolArray() {
    char* a1[] = {"a", "b", "c", "d", "e"};
    int size = 5;
    char* bot =  "~";
    Alphabet* alpha1 = createAlphabet(a1, 5, bot);

    SymbolArray* s = createRandomSymbolArray(alpha1, 20); // create a 20 character long symbol array
    for (int i = 0; i < s->size; i++) {
        printf("%s\n", s->symbols[i]);
    }
    deleteAlphabet(alpha1);
    deleteSymbolArray(s);
}

void test_permutations() {
    char letters[] = "abc"; 
   

    char** perms = permutations(letters);

    int n = strlen(letters);
    for (int i = 0; i < factorial(n); i++) {
        printf("%s\n", perms[i]);
        free(perms[i]); // Free each permutation string
    }
    free(perms);
}

int main(void) {
    UNITY_BEGIN();
    // RUN_TEST(test_symbol_constructor);
    // RUN_TEST(test_alphabet_constructor);
    // RUN_TEST(test_createRandomSymbolArray);
    RUN_TEST(test_permutations);
    return UNITY_END();
}