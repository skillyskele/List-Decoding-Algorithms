#include <stdio.h>
#include "../include/sync_string.h"
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
    char s1[] = "abcde";
    char s2[] = "ace";
    int lcs = find_LCS(s1, s2);
    TEST_ASSERT_EQUAL_INT(3, lcs);
}

void test_find_LCS_EmptyString(void) {
    char s1[] = "";
    char s2[] = "ace";
    TEST_ASSERT_EQUAL_INT(0, find_LCS(s1, s2));
}


void test_find_LCS_NoCommonSubsequence(void) {
    char s1[] = "abc";
    char s2[] = "def";
    TEST_ASSERT_EQUAL_INT(0, find_LCS(s1, s2));
}


void test_find_LCS_IdenticalStrings(void) {
    char s1[] = "abcdef";
    char s2[] = "abcdef";
    TEST_ASSERT_EQUAL_INT(6, find_LCS(s1, s2));
}


void test_find_LCS_SubsequenceAtEnd(void) {
    char s1[] = "xyzabc";
    char s2[] = "abc";
    int lcs = find_LCS(s1, s2);
    TEST_ASSERT_EQUAL_INT(3, lcs);
}

// This test case copies the LCS_Simple test
void test_edit_distance_Simple(void) {
    char *S = "aceabcdey";
    int i = 0, j = 3, k = 8;
    TEST_ASSERT_EQUAL_INT(3, edit_distance(S, i, j, k));    
}


/**
 * Test for the synchronization string checker function
 */
void test_SyncStringFunction(void) {
    // Test synchronization strings
    const char* sync_string_1 = "123456789x";
    const char* sync_string_2 = "abcdefghij";

    // Test parameters
    int n = 10; // Length of the synchronization strings
    double epsilon = 0.1; // Epsilon value for the check

    TEST_ASSERT_TRUE(synchronization_string_checker(sync_string_1, n, epsilon));
    TEST_ASSERT_TRUE(synchronization_string_checker(sync_string_2, n, epsilon));
}

int main(void) {
    UNITY_BEGIN();
    //RUN_TEST(test_SyncStringFunction);
    RUN_TEST(test_find_LCS_Simple);
    RUN_TEST(test_find_LCS_EmptyString);
    RUN_TEST(test_find_LCS_NoCommonSubsequence);
    RUN_TEST(test_find_LCS_IdenticalStrings);
    RUN_TEST(test_find_LCS_SubsequenceAtEnd);

    RUN_TEST(test_edit_distance_Simple);

    return UNITY_END();
}
