#ifndef utils_h
#define utils_h

#include <stdio.h>

char* read_file(const char *filename);
void parse_numbers(char* line_start, int* accumulator, int count);

#endif /* utils_h */
