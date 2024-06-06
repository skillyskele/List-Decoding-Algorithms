#ifndef SYNC_STRING_H
#define SYNC_STRING_H

#include <stdbool.h>

int find_LCS(const char* s1, const char* s2);
int edit_distance(const char *s1, int s1_len, const char *s2, int s2_len);
bool synchronization_string_checker(const char *S, int n, double epsilon);
bool synchronization_string_checker(const char* S, int n, double epsilon);
void minimum_epsilon_finder(const char* S, int n);
double compute_rsd(const char *S, const char *S_prime);


#endif 
