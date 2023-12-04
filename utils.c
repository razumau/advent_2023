#include <stdlib.h>
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
