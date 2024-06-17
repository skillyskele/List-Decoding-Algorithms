#ifndef SYNC_STRING_H
#define SYNC_STRING_H
#include <stdbool.h>
#include "symbol_alphabet.h"

int max(int a, int b);
int find_LCS(const SymbolArray *sa1, const SymbolArray *sa2);
int edit_distance(const SymbolArray *sa1, const SymbolArray *sa2);
void arraycpy(char** dest, char** src, int n);
bool synchronization_string_checker(const char *S, int n, double epsilon);
void minimum_epsilon_finder(const char* S, int n);
double compute_rsd(const char *S, const char *S_prime);


#endif 
