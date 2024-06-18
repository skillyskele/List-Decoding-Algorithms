#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
    deleteSymbolArray(sa1);
    deleteSymbolArray(sa2);
}

void test_find_LCS_EmptyString(void) {
    char* s1[] = {""};
    char* s2[] = {"a", "c", "e"};
    SymbolArray *sa1 = createSymbolArray(s1, 1);
    SymbolArray *sa2 = createSymbolArray(s2, 3);

    int lcs = find_LCS(sa1, sa2);
    TEST_ASSERT_EQUAL_INT(0, lcs);

    deleteSymbolArray(sa1);
    deleteSymbolArray(sa2);
}

void test_find_LCS_NoCommonSubsequence(void) {
    char* s1[] = {"a", "b", "c"};
    char* s2[] = {"d", "e", "f"};
    SymbolArray *sa1 = createSymbolArray(s1, 3);
    SymbolArray *sa2 = createSymbolArray(s2, 3);

    int lcs = find_LCS(sa1, sa2);
    TEST_ASSERT_EQUAL_INT(0, lcs);

    deleteSymbolArray(sa1);
    deleteSymbolArray(sa2);
}

void test_find_LCS_IdenticalStrings(void) {
    char* s1[] = {"a", "b", "c", "d", "e", "f"};
    char* s2[] = {"a", "b", "c", "d", "e", "f"};
    SymbolArray *sa1 = createSymbolArray(s1, 6);
    SymbolArray *sa2 = createSymbolArray(s2, 6);

    int lcs = find_LCS(sa1, sa2);
    TEST_ASSERT_EQUAL_INT(6, lcs);

    deleteSymbolArray(sa1);
    deleteSymbolArray(sa2);
}

void test_find_LCS_SubsequenceAtEnd(void) {
    char* s1[] = {"x", "y", "z", "a", "b", "c"};
    char* s2[] = {"a", "b", "c"};
    SymbolArray *sa1 = createSymbolArray(s1, 6);
    SymbolArray *sa2 = createSymbolArray(s2, 3);

    int lcs = find_LCS(sa1, sa2);
    TEST_ASSERT_EQUAL_INT(3, lcs);

    deleteSymbolArray(sa1);
    deleteSymbolArray(sa2);
}

void test_edit_distance_Simple(void) {
    char* S[] = {"a", "b", "c", "d", "e", "f", "g", "h"};
    int i = 0, j = 3, k = 8; // note k actually points to one after h.

    char* s1[] = {"a", "c", "e"};
    char* s2[] = {"a", "b", "c", "d", "e"};
    // for (int i = 0; i < j; i++) {
    //     s2[j] = S[i];
    // }
    //arraycpy(s2, S + j, k-j);
    SymbolArray *sa1 = createSymbolArray(s1, 3);
    SymbolArray *sa2 = createSymbolArray(s2, 5);

    // Call edit_distance
    TEST_ASSERT_EQUAL_INT(2, edit_distance(sa1, sa2));

      
    deleteSymbolArray(sa1);
    deleteSymbolArray(sa2);
}


int main(void) {
    UNITY_BEGIN();
    
    // RUN_TEST(test_find_LCS_Simple);
    // RUN_TEST(test_find_LCS_EmptyString);
    // RUN_TEST(test_find_LCS_NoCommonSubsequence);
    // RUN_TEST(test_find_LCS_IdenticalStrings);
    // RUN_TEST(test_find_LCS_SubsequenceAtEnd);

     RUN_TEST(test_edit_distance_Simple);
    // RUN_TEST(test_edit_distance_EmptyString);
    // RUN_TEST(test_edit_distance_TwoEmptyStrings);
    // RUN_TEST(test_edit_distance_SmallestStrings);
    // RUN_TEST(test_edit_distance_NoCommonSubsequence);
    // RUN_TEST(test_edit_distance_IdenticalStrings);
    return UNITY_END();
}
