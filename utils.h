#ifndef utils_h
#define utils_h

#include <stdio.h>

char* read_file(const char *filename);
void parse_numbers(char* line_start, int* accumulator, int count);
void parse_all_numbers(char* line_start, long long* accumulator);
char** readLines(const char *filename, int *lineCount);

#endif /* utils_h */
