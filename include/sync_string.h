#ifndef SYNC_STRING_H
#define SYNC_STRING_H

#include <stdbool.h>

int edit_distance(const char *S, int i, int j, int k);
bool synchronization_string_checker(const char *S, int n, double epsilon);

#endif 
