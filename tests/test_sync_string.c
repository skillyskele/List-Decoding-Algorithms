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
    char** s1 = (char**)malloc(5 * sizeof(char*));
    char** s2 = (char**)malloc(3 * sizeof(char*));

    s1[0] = strdup("a");
    s1[1] = strdup("b");
    s1[2] = strdup("c");
    s1[3] = strdup("d");
    s1[4] = strdup("e");

    s2[0] = strdup("a");
    s2[1] = strdup("c");
    s2[2] = strdup("e");

    SymbolArray *sa1 = createSymbolArray(s1, 5);
    SymbolArray *sa2 = createSymbolArray(s2, 3);

    int lcs = find_LCS(sa1, sa2);
    TEST_ASSERT_EQUAL_INT(3, lcs);

    deleteSymbolArray(sa1);
    deleteSymbolArray(sa2);

    for (int i = 0; i < 5; i++) {
        free(s1[i]);
    }
    for (int i = 0; i < 3; i++) {
        free(s2[i]);
    }
    free(s1);
    free(s2);
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

void test_edit_distanceOneLetter(void) {
    char **s1 = malloc(2 * sizeof(char*));
    char **s2 = malloc(1 * sizeof(char*));
    s1[0] = strdup("b");
    s1[1] = strdup("a");
    s2[0] = strdup("b");
    SymbolArray *sa1 = createSymbolArray(s1, 2);
    SymbolArray *sa2 = createSymbolArray(s2, 1);
    // TEST_ASSERT_EQUAL_INT(1, edit_distance(sa1, sa2));
    free(s1[0]);
    free(s1[1]);
    free(s2[0]);
    free(s1);
    free(s2);
    deleteSymbolArray(sa1);
    deleteSymbolArray(sa2);
}

void test_edit_distance_Simple(void) {
    char *values[] = {"a", "b", "c", "d", "e", "f", "g", "h"};
    char **S = (char**)malloc(8 * sizeof(char*));

    for (int i = 0; i < 8; i++) {
        S[i] = strdup(values[i]);
    }
    int i = 0, j = 3, k = 8; 
    
    char** s1 = malloc((j)*sizeof(char*));
    // for (int i = 0; i < j; i++) {
    //     s1[i] = S[i];
    // }
    arraycpy(s1, S + i, j); // one can malloc the substring


    char** s2 = malloc((k-j)*sizeof(char*));
    arraycpy(s2, S + i, k-j);

    SymbolArray *sa1 = createSymbolArray(s1, 3); // simply points s->symbols[i] to s2, which has been malloc'd
    SymbolArray *sa2 = createSymbolArray(s2, 5); // in this case, malloc-ing s1 and s2 wasn't needed, S was never modified, nor was s1 nor s2.

    // could just malloc it once, and then everything just points to that one malloc'd string in the heap.

    // Call edit_distance
    TEST_ASSERT_EQUAL_INT(2, edit_distance(sa1, sa2));

    
    for (int i = 0; i < 3; i++) {
        free(s1[i]);
    }
    for (int i = 0; i < 5; i++) {
        free(s2[i]);
    }
    free(s1); // if it ws malloc'd, then it must be freed!!!
    free(s2); 
    deleteSymbolArray(sa1);
    deleteSymbolArray(sa2);
    for (int i = 0; i < 8; i++) {
        free(S[i]);
    }
    free(S);

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

// if you declare your strings statically, so NOT on the heap, createSymbolArray will simply point to it in static memory...no problem. but it won't be able to modify that string.
void test_edit_distance_SmallestStrings(void) {
    char* s1[]  = {"b"};
    char* s2[] = {"b"};
    SymbolArray *sa1 = createSymbolArray(s1, 1);
    SymbolArray *sa2 = createSymbolArray(s2, 1);

    TEST_ASSERT_EQUAL_INT(0, edit_distance(sa1, sa2));
      
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

void test_edit_distance_RepeatedLetterStrings(void) {
    char* s1[]  = {"a", "aa", "aaa"};
    char* s2[] = {"aaaa", "aaaaa", "barry"};
    SymbolArray *sa1 = createSymbolArray(s1, 3);
    SymbolArray *sa2 = createSymbolArray(s2, 3);

    TEST_ASSERT_EQUAL_INT(6, edit_distance(sa1, sa2));
      
    deleteSymbolArray(sa1);
    deleteSymbolArray(sa2);

}

// the 's' parameter being passed in here does NOT have to be malloc'd
void test_sync_string_checker(char **s, int n, float e) {
    char *s1 = symbolArrayPrinter(s, n);
    printf("Testing with string '%s'\n", s1);
    free(s1);
    synchronization_string_checker(s, n, e); //this function WILL malloc and free substrings as it goes. 
}

void test_minimum_epsilon(char **s, int n) {
    char *s1 = symbolArrayPrinter(s, n);
    printf("Testing with string '%s'\n", s1);
    free(s1);
    minimum_epsilon_finder(s, n); //this function WILL malloc and free substrings as it goes. 
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

void test_epsilon_sync_string_maker(void) {
    char** a1 = malloc(3 * sizeof(char*));
    a1[0] = strdup("a");
    a1[1] = strdup("b");
    a1[2] = strdup("c");    
    int size = 3;
    char* bot =  "~";
    Alphabet* alpha1 = createAlphabet(a1, 3, bot);
    epsilon_sync_string_maker(1, 5, alpha1);

    deleteAlphabet(alpha1);
    for (int i = 0; i < 3; i++) {
        free(a1[i]);
    }
    free(a1);

}

//skillyskele <-- github
//nathan kim <-- linkedin
//ksotillo <-- github 



void test_SyncStringABA(void) {
    
    int n = 3;
    double e1 = 0.67;
    double e2 = 0.65;
    char** ABA = malloc(3 * sizeof(char*));
    ABA[0] = strdup("a");
    ABA[1] = strdup("b");
    ABA[2] = strdup("a");

    TEST_ASSERT_TRUE(synchronization_string_checker(ABA, n, e1));
    TEST_ASSERT_FALSE(synchronization_string_checker(ABA, n, e2));
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
    // RUN_TEST(test_edit_distance_RepeatedLetterStrings);
    // RUN_TEST(test_edit_distanceOneLetter);


    // char* ABA_strings[] = {"a", "b", "a"};
    // test_sync_string_checker(ABA_strings, 3, 0.66);


    // example of how it'd look if the string was malloc'd first
    // char** ABCDE = malloc(5 * sizeof(char*));
    // char* ABCDE_strings[] = {"a", "b", "c", "d", "e"};
    // for (int i = 0; i < 5; i++) {
    //     ABCDE[i] = strdup(ABCDE_strings[i]);
    // }
    // test_minimum_epsilon(ABCDE_strings, 5);
    // for (int i = 0; i < 5; i++) {
    //     free(ABCDE[i]);
    // }
    // free(ABCDE);

    // char** A_AA_AAA = malloc(3 * sizeof(char*));
    // char* A_AA_AAA_strings[] = {"a", "aa", "aaa"};
    // for (int i = 0; i < 3; i++) {
    //     A_AA_AAA[i] = strdup(A_AA_AAA_strings[i]);
    // }
    // test_minimum_epsilon(A_AA_AAA, 3);
    // for (int i = 0; i < 3; i++) {
    //     free(A_AA_AAA[i]);
    // }
    // free(A_AA_AAA);

    // char* ABC[] = {"a", "b", "c"};
    
    // RUN_TEST(test_SyncStringABA);
   

    RUN_TEST(test_epsilon_sync_string_maker);

    // test_symbolArrayPrinter();
    return UNITY_END();
}
