#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../include/symbol_alphabet.h"
#include "unity.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_constructor() {
    char* symbols[] = {"symbol1", "symbol2", "symbol3"};
    int size = 3;
    SymbolArray* s = createSymbolArray(symbols, size);
    TEST_ASSERT_NOT_NULL(s);
    TEST_ASSERT_EQUAL(size, s->size);
    for (int i = 0; i < size; i++) {
        TEST_ASSERT_EQUAL_STRING(symbols[i], s->symbols[i]);
    }
    deleteSymbolArray(s);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_constructor);
    return UNITY_END();
}