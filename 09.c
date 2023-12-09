#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <string.h>
#include <ctype.h>

long extrapolate(char* line) {
    long numbers[100] = {0};
    int numbers_count = parse_all_numbers(line, numbers);
    
    long *top_row = calloc(numbers_count, sizeof(long));
    memcpy(top_row, numbers, numbers_count * sizeof(long));
    long *bottom_row;
    long sum = top_row[numbers_count - 1];
    
    do {
        bottom_row = calloc(numbers_count - 1, sizeof(long));
        for (int i = 0; i < numbers_count - 1; i++) {
            bottom_row[i] = top_row[i + 1] - top_row[i];
        }
        sum += bottom_row[numbers_count - 2];
        printf("sum is now %ld\n", sum);
        numbers_count--;
        memcpy(top_row, bottom_row, numbers_count * sizeof(long));
        
    } while (bottom_row[0] || bottom_row[1]);

    printf("returning %ld\n\n", sum);
    return sum;
}

long extrapolate_left(char* line) {
    long numbers[100] = {0};
    int numbers_count = parse_all_numbers(line, numbers);
    
    long *top_row = calloc(numbers_count, sizeof(long));
    memcpy(top_row, numbers, numbers_count * sizeof(long));
    long *bottom_row;
    long sum = top_row[0];
    printf("sum starts with %ld\n", sum);
    int sign = -1;
    
    do {
        bottom_row = calloc(numbers_count - 1, sizeof(long));
        for (int i = 0; i < numbers_count - 1; i++) {
            bottom_row[i] = top_row[i + 1] - top_row[i];
        }
        sum += bottom_row[0] * sign;
        sign *= -1;
        printf("sum is now %ld\n", sum);
        numbers_count--;
        memcpy(top_row, bottom_row, numbers_count * sizeof(long));
        
    } while (bottom_row[0] || bottom_row[1]);

    printf("returning %ld\n\n", sum);
    return sum;
}



long solve_09(void) {
    int lines_count;
    char **input = readLines("/Users/juryrazumau/advent_2023/input/09_b.txt", &lines_count);
    int sum = 0;
    for (int i = 0; i < lines_count; i++) {
        printf("line is %s\n", input[i]);
        sum += extrapolate(input[i]);
    }
    return sum;
}


int solve_09_b(void) {
    int lines_count;
    char **input = readLines("/Users/juryrazumau/advent_2023/input/09_b.txt", &lines_count);
    int sum = 0;
    for (int i = 0; i < lines_count; i++) {
        printf("line is %s\n", input[i]);
        sum += extrapolate_left(input[i]);
    }
    return sum;
}
