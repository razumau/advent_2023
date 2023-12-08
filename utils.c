#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

char* read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(length + 1);
    if (!buffer) {
        perror("Error allocating memory");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';
    fclose(file);

    return buffer;
}

void parse_numbers(char* line_start, int* accumulator, int count) {
    char *number_start = line_start;
    char *number_end;
    for (int i = 0; i < count; i++) {
        accumulator[i] = strtol(number_start, &number_end, 10);
        number_start = number_end;
    }
}

void parse_all_numbers(char* line_start, long long* accumulator) {
    char *number_start = line_start;
    char *number_end;
    for (int i = 0;; i++) {
        accumulator[i] = strtol(number_start, &number_end, 10);
        if (number_start == number_end) { break; }
        number_start = number_end;
    }
}

char** readLines(const char *filename, int *lineCount) {
    FILE *file = fopen(filename, "r");
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t nread;

    int capacity = 100;
    char **lines = malloc(capacity * sizeof(char*));
    *lineCount = 0;

    while ((nread = getline(&buffer, &bufsize, file)) != -1) {
        if (buffer[nread - 1] == '\n') {
            buffer[nread - 1] = '\0';
        }

        if (*lineCount >= capacity) {
            capacity *= 2;
            lines = realloc(lines, capacity * sizeof(char*));
        }

        lines[*lineCount] = strdup(buffer);
        (*lineCount)++;
    }

    free(buffer);
    return lines;
}

