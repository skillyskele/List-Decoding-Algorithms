#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../include/sync_string.h"
#include "../include/symbol_alphabet.h"
#include "unity.h"

/**
 * Unity provides optional functions that will run 
 * before and after unit tests, in case additional 
 * resources need to be set up and torn down
 */
void setUp(void) {
}

void tearDown(void) {
}

void test_find_LCS_Simple(void) {
    char* s1[] = {"a", "b", "c", "d", "e"};
    char* s2[] = {"a", "c", "e"};
    SymbolArray *sa1 = createSymbolArray(s1, 5);
    SymbolArray *sa2 = createSymbolArray(s2, 3);

    int lcs = find_LCS(sa1, sa2);
    TEST_ASSERT_EQUAL_INT(3, lcs);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_find_LCS_Simple);
    return UNITY_END();
}
