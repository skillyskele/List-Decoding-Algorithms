#ifndef SYNC_STRING_H
#define SYNC_STRING_H
#include <stdbool.h>
#include "symbol_alphabet.h"


int max(int a, int b);
int find_LCS(const SymbolArray *sa1, const SymbolArray *sa2);
int edit_distance(const SymbolArray *sa1, const SymbolArray *sa2);
void arraycpy(char** dest, char** src, int n);
bool synchronization_string_checker(char **S, int n, double epsilon);
double minimum_epsilon_finder(char** S, int n);
double compute_rsd(char *S, const char *S_prime);
char* symbolArrayPrinter(char** s, int n);
void epsilon_sync_string_maker(double epsilon, int n, Alphabet* a); 

#endif 
