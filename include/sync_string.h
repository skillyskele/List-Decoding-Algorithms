#ifndef SYNC_STRING_H
#define SYNC_STRING_H

#include <stdbool.h>

int find_LCS(const char* s1, const char* s2);
int edit_distance(const char *S, int i, int j, int k);
bool synchronization_string_checker(const char *S, int n, double epsilon);
bool synchronization_string_checker(const char* S, int n, double epsilon);
void minimum_epsilon_finder(const char* S, int n);

#endif 
