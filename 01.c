#include <stdio.h>
#include "utils.h"
#include <string.h>

int count(char* lines) {
    int sum = 0;
    const char *delimiter = "\n";
    char *line = strtok(lines, delimiter);
    
    while (line != NULL) {
        int left = 0, right = 0;
        for (int i = 0; i < strlen(line); i++) {
            if (line[i] >= 48 && line[i] <= 57) {
                left = line[i] - 48;
                break;
            }
        }
        for (int i = strlen(line) - 1; i >= 0; i--) {
            if (line[i] >= 48 && line[i] <= 57) {
                right = line[i] - 48;
                break;
            }
        }
        sum += left * 10 + right;
        line = strtok(NULL, delimiter);
    }
    return sum;
}

int solve_01(void) {
    char* input = read_file("/Users/juryrazumau/advent_2023/input/01_b.txt");
    return count(input);
}


int solve_01_b(void) {
    char* input = read_file("/Users/juryrazumau/advent_2023/input/01_b.txt");
    const char *delimiter = "\n";
    char *line = strtok(input, delimiter);
    int sum = 0;
    const char digits[10][10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    
    while (line != NULL) {
        int left = 0, right = 0;
        for (int i = 0; i < strlen(line); i++) {
            if (line[i] >= 48 && line[i] <= 57) {
                left = line[i] - 48;
                break;
            }
            
            for (int j = 0; j < 10; j++) {
                if (!strncmp(line + i, digits[j], strlen(digits[j]))) {
                    left = j;
                }
            }
            if (left) break;
        }
        
        for (int i = strlen(line) - 1; i >= 0; i--) {
            if (line[i] >= 48 && line[i] <= 57) {
                right = line[i] - 48;
                break;
            }
            
            for (int j = 0; j < 10; j++) {
                if (!strncmp(line + i, digits[j], strlen(digits[j]))) {
                    right = j;
                }
            }
            if (right) break;
        }
        sum += left * 10 + right;
        printf("sum for line: %d\n", left * 10 + right);
        line = strtok(NULL, delimiter);
    }
    return sum;
}
