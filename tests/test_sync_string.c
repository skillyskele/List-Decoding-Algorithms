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
    RUN_TEST(test_SyncStringFunction);
    return UNITY_END();
}
