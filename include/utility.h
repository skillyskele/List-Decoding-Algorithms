#ifndef UTILITY_H
#define UTILITY_H

#include "../include/symbol_alphabet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b);
void arraycpy(char** dest, char** src, int n);
char* symbolArrayPrinter(char** s, int n);
void rotateRight(char* str, int len);
char** random_string(Alphabet* a, int arraySize);
char** random_sampling(char** s, int n, Alphabet* a, double epsilon);



#endif 
