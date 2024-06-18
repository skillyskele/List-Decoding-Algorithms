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
    // free any dynamically allocated test strings
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
    
    char** s1 = malloc((j)*sizeof(char*));
    // for (int i = 0; i < j; i++) {
    //     s1[i] = S[i];
    // }
    arraycpy(s1, S + i, j); // one can malloc the substring


    char* s2[] = {"a", "b", "c", "d", "e"}; // or one can have it in read only memory

    SymbolArray *sa1 = createSymbolArray(s1, 3);
    SymbolArray *sa2 = createSymbolArray(s2, 5);
    // Call edit_distance
    TEST_ASSERT_EQUAL_INT(2, edit_distance(sa1, sa2));

    // This is the improper way of freeing s1, s1 is only one pointer
    // for (int i = 0; i < j; i++) {
    //     free(s1[i]);
    // }
    free(s1); // if it ws malloc'd, then it must be freed!!!
      
    deleteSymbolArray(sa1);
    deleteSymbolArray(sa2);

}

// NOTE: if s1 = {""}, then a memory leak occurs. No idea why.
void test_edit_distance_EmptyString(void) {
    char* s1[]  = {};
    char* s2[] = {"a", "b", "c"};
    SymbolArray *sa1 = createSymbolArray(s1, 0);
    SymbolArray *sa2 = createSymbolArray(s2, 3);

    TEST_ASSERT_EQUAL_INT(3, edit_distance(sa1, sa2));
      
    deleteSymbolArray(sa1);
    deleteSymbolArray(sa2);

}

void test_edit_distance_TwoEmptyStrings(void) {
    char* s1[]  = {};
    char* s2[] = {};
    SymbolArray *sa1 = createSymbolArray(s1, 0);
    SymbolArray *sa2 = createSymbolArray(s2, 0);

    TEST_ASSERT_EQUAL_INT(0, edit_distance(sa1, sa2));
      
    deleteSymbolArray(sa1);
    deleteSymbolArray(sa2);

}

void test_edit_distance_SmallestStrings(void) {
    char* s1[]  = {"j"};
    char* s2[] = {"b"};
    SymbolArray *sa1 = createSymbolArray(s1, 1);
    SymbolArray *sa2 = createSymbolArray(s2, 1);

    TEST_ASSERT_EQUAL_INT(2, edit_distance(sa1, sa2));
      
    deleteSymbolArray(sa1);
    deleteSymbolArray(sa2);
}

void test_edit_distance_NoCommonSubsequence(void) {
    char* s1[]  = {"a", "b", "c"};
    char* s2[] = {"d", "e", "fg"};
    SymbolArray *sa1 = createSymbolArray(s1, 3);
    SymbolArray *sa2 = createSymbolArray(s2, 3);

    TEST_ASSERT_EQUAL_INT(6, edit_distance(sa1, sa2));
      
    deleteSymbolArray(sa1);
    deleteSymbolArray(sa2);

}

void test_edit_distance_IdenticalStrings(void) {
    char* s1[]  = {"a", "b", "c"};
    char* s2[] = {"a", "b", "c"};
    SymbolArray *sa1 = createSymbolArray(s1, 3);
    SymbolArray *sa2 = createSymbolArray(s2, 3);

    TEST_ASSERT_EQUAL_INT(0, edit_distance(sa1, sa2));
      
    deleteSymbolArray(sa1);
    deleteSymbolArray(sa2);

}

void test_minimum_epsilon(char **s, int n) {
    char *s1 = symbolArrayPrinter(s, n);
    printf("Testing with string '%s'\n", s1);
    free(s1);
    minimum_epsilon_finder(s, n);
}

void test_symbolArrayPrinter(void) {
    // Allocate memory for an array of 6 string pointers
    char** s1 = malloc(6 * sizeof(char*));
    if (!s1) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    // Initialize each pointer to point to the string "a"
    for (int i = 0; i < 6; i++) {
        s1[i] = "a";
    }

    // Call symbolArrayPrinter to concatenate the symbols
    char* s1_string = symbolArrayPrinter(s1, 6); // Ensure you pass the length of the array
    if (s1_string) {
        printf("%s\n", s1_string); // Output should be "aaaaaa"
        free(s1_string); // Free the memory allocated by symbolArrayPrinter
    }

    // Free the allocated memory for the array of pointers
    free(s1);
}


int main(void) {
    UNITY_BEGIN();
    
    // RUN_TEST(test_find_LCS_Simple);
    // RUN_TEST(test_find_LCS_EmptyString);
    // RUN_TEST(test_find_LCS_NoCommonSubsequence);
    // RUN_TEST(test_find_LCS_IdenticalStrings);
    // RUN_TEST(test_find_LCS_SubsequenceAtEnd);

    // RUN_TEST(test_edit_distance_Simple);
    // RUN_TEST(test_edit_distance_EmptyString);
    // RUN_TEST(test_edit_distance_TwoEmptyStrings);
    // RUN_TEST(test_edit_distance_SmallestStrings);
    // RUN_TEST(test_edit_distance_NoCommonSubsequence);
    // RUN_TEST(test_edit_distance_IdenticalStrings);
    char* ABA[] = {"a", "b", "a"};
    test_minimum_epsilon(ABA, 3);
    // test_minimum_epsilon("abcdefghij");
    // test_minimum_epsilon("123456789x");
    // test_minimum_epsilon("nathan_and_harry");
    // test_minimum_epsilon("thisis");

    //test_symbolArrayPrinter();
    return UNITY_END();
}
