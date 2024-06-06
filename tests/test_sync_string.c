#include <stdio.h>
#include <string.h>
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

void test_edit_distance_Simple(void) {
    char *S = "aceabcdey";
    int i = 0, j = 3, k = 8;

    // Extract substrings
    char s1[4]; // Length = j - i = 3
    strncpy(s1, S + i, j - i);
    s1[j - i] = '\0';

    char s2[6]; // Length = k - j = 5
    strncpy(s2, S + j, k - j);
    s2[k - j] = '\0';

    // Call edit_distance
    TEST_ASSERT_EQUAL_INT(2, edit_distance(s1, j - i, s2, k - j));   
}

void test_edit_distance_EmptyString(void) {
    char *S = "abcy";
    int i = 0, j = 0, k = 3;

    // Extract substrings
    char s1[1]; // Length = j - i = 0
    strncpy(s1, S + i, j - i);
    s1[j - i] = '\0';

    char s2[4]; // Length = k - j = 3
    strncpy(s2, S + j, k - j);
    s2[k - j] = '\0';

    // Call edit_distance
    TEST_ASSERT_EQUAL_INT(3, edit_distance(s1, j - i, s2, k - j));
}

// In practice, you should never compare two empty strings, since i < j < k, and string length is always at least 2
void test_edit_distance_TwoEmptyStrings(void) {
    char *S = "";
    int i = 0, j = 0, k = 0;

    // Extract substrings
    char s1[1]; // Length = j - i = 0
    strncpy(s1, S + i, j - i);
    s1[j - i] = '\0';

    char s2[1]; // Length = k - j = 0
    strncpy(s2, S + j, k - j);
    s2[k - j] = '\0';

    // Call edit_distance
    TEST_ASSERT_EQUAL_INT(0, edit_distance(s1, j - i, s2, k - j));
}

void test_edit_distance_SmallestStrings(void) {
    char *S = "jb";
    int i = 0, j = 1, k = 2;

    // Extract substrings
    char s1[2]; // Length = j - i = 1
    strncpy(s1, S + i, j - i);
    s1[j - i] = '\0';

    char s2[2]; // Length = k - j = 1
    strncpy(s2, S + j, k - j);
    s2[k - j] = '\0';

    // Call edit_distance
    TEST_ASSERT_EQUAL_INT(2, edit_distance(s1, j - i, s2, k - j));
}

void test_edit_distance_NoCommonSubsequence(void) {
    char *S = "abcdefy";
    int i = 0, j = 3, k = 6;

    // Extract substrings
    char s1[4]; // Length = j - i = 3
    strncpy(s1, S + i, j - i);
    s1[j - i] = '\0';

    char s2[4]; // Length = k - j = 3
    strncpy(s2, S + j, k - j);
    s2[k - j] = '\0';

    // Call edit_distance
    TEST_ASSERT_EQUAL_INT(6, edit_distance(s1, j - i, s2, k - j));    
}

void test_edit_distance_IdenticalStrings(void) {
    char *S = "abcabcy";
    int i = 0, j = 3, k = 6;

    // Extract substrings
    char s1[4]; // Length = j - i = 3
    strncpy(s1, S + i, j - i);
    s1[j - i] = '\0';

    char s2[4]; // Length = k - j = 3
    strncpy(s2, S + j, k - j);
    s2[k - j] = '\0';

    // Call edit_distance
    TEST_ASSERT_EQUAL_INT(0, edit_distance(s1, j - i, s2, k - j));   
}

void test_SyncStringFailCases(void) {
    const char* sync_string_1 = "aa";
    const char* sync_string_2 = "aabaa";
    const char* sync_string_3 = "abababab";
    const char* sync_string_4 = "cccccc";
    const char* sync_string_5 = "xyzxyzxyz";
    
    int n1 = 2;
    int n2 = 5;
    int n3 = 8;
    int n4 = 6;
    int n5 = 9;
    double epsilon = .9;

    TEST_ASSERT_FALSE(synchronization_string_checker(sync_string_1, n1, epsilon));
    TEST_ASSERT_FALSE(synchronization_string_checker(sync_string_2, n2, epsilon));
    TEST_ASSERT_FALSE(synchronization_string_checker(sync_string_3, n3, epsilon));
    TEST_ASSERT_FALSE(synchronization_string_checker(sync_string_4, n4, epsilon));
    TEST_ASSERT_FALSE(synchronization_string_checker(sync_string_5, n5, epsilon));
}

void test_SyncStringABA(void) {
    const char* sync_string = "aba";
    
    int n = 3;
    double epsilon1 = 0.67;
    double epsilon2 = 0.65;

    TEST_ASSERT_TRUE(synchronization_string_checker(sync_string, n, epsilon1));
    TEST_ASSERT_FALSE(synchronization_string_checker(sync_string, n, epsilon2));
}

void test_minimum_epsilon_ABA(char *s) {    
    int n = strlen(s);

    printf("Testing with string '%s'\n", s);
    minimum_epsilon_finder(s, n);
}

/**
 * Test for the synchronization string checker function
 */
void test_SyncStringTrivialCase(void) {
    // Test synchronization strings 
    const char* sync_string_1 = "123456789x";
    const char* sync_string_2 = "abcdefghij";

    // Test parameters
    int n = 10; // Length of the synchronization strings
    double epsilon = 0.1; // Epsilon value for the check

    TEST_ASSERT_TRUE(synchronization_string_checker(sync_string_1, n, epsilon));
    TEST_ASSERT_TRUE(synchronization_string_checker(sync_string_2, n, epsilon));
}

void test_compute_RSD(void) {
    const char* s1 = "abc";
    const char* s2 = "a";

    TEST_ASSERT_EQUAL_INT(1, compute_rsd(s1, s2));
}

int main(void) {
    UNITY_BEGIN();
    // RUN_TEST(test_SyncStringFunction);
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
    // RUN_TEST(test_SyncStringFailCases);
    // test_minimum_epsilon_ABA("aba");
    // test_minimum_epsilon_ABA("abcdefghij");
    // test_minimum_epsilon_ABA("123456789x");
    // test_minimum_epsilon_ABA("nathan_and_harry");
    // test_minimum_epsilon_ABA("thisis");

    //RUN_TEST(test_SyncStringTrivialCase);


    //RUN_TEST(test_SyncStringABA);
    RUN_TEST(test_compute_RSD);
    return UNITY_END();
}
