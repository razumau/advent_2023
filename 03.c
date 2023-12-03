#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <string.h>
#include <ctype.h>

//#define SIZE 11
#define SIZE 141

int has_symbol(char engine[][SIZE], int i, int j) {
    if (i < 0 || j < 0 || i >= SIZE - 1 || j >= SIZE - 1 || isdigit(engine[i][j]) || engine[i][j] == '.' || engine[i][j] == '\0') {
        return 0;
    }
    return 1;
}

int has_symbol_nearby(char engine[][SIZE], int i, int j) {
    return has_symbol(engine, i - 1, j - 1) ||
           has_symbol(engine, i, j - 1) ||
           has_symbol(engine, i + 1, j - 1) ||
           has_symbol(engine, i - 1, j + 1) ||
           has_symbol(engine, i, j + 1) ||
           has_symbol(engine, i + 1, j + 1) ||
           has_symbol(engine, i - 1, j) ||
           has_symbol(engine, i + 1, j);
}

struct point {
    int x;
    int y;
};

int has_gear(char engine[][SIZE], int i, int j) {
    if (i < 0 || j < 0 || i >= SIZE - 1 || j >= SIZE - 1) {
        return 0;
    }
    if (engine[i][j] == '*') {
        return 1;
    }
    return 0;
}

struct point find_gear(char engine[][SIZE], int i, int j) {
    if (has_gear(engine, i - 1, j - 1)) { return (struct point) {i - 1, j - 1}; }
    if (has_gear(engine, i, j - 1)) { return (struct point) {i, j - 1}; }
    if (has_gear(engine, i + 1, j - 1)) { return (struct point) {i + 1, j - 1}; }
    if (has_gear(engine, i - 1, j + 1)) { return (struct point) {i - 1, j + 1}; }
    if (has_gear(engine, i, j + 1)) { return (struct point) {i, j + 1}; }
    if (has_gear(engine, i + 1, j + 1)) { return (struct point) {i + 1, j + 1}; }
    if (has_gear(engine, i - 1, j)) { return (struct point) {i - 1, j}; }
    if (has_gear(engine, i + 1, j)) { return (struct point) {i + 1, j}; }
    
    return (struct point) {-1, -1};
}

int solve_03(void) {
    char* input = read_file("/Users/juryrazumau/advent_2023/input/03_b.txt");
    char engine[SIZE][SIZE];
    int sum = 0;
    
    const char *delimiter = "\n";
    char *line = strtok(input, delimiter);
    for (int i = 0; (i < SIZE) && (line != NULL); i++){
        strcpy(engine[i], line);
        line = strtok(NULL, delimiter);
    }
    for (int i = 0; i < SIZE; i++){
        int current_number = 0;
        int has_symbol = 0;
        for (int j = 0; j < SIZE; j++){
            if (isdigit(engine[i][j])) {
                current_number = current_number * 10 + engine[i][j] - 48;
                if (!has_symbol) {
                    has_symbol = has_symbol_nearby(engine, i, j);
                }
            } else {
                if (has_symbol) {
                    sum += current_number;
                }
                current_number = 0;
                has_symbol = 0;
            }
        }
    }
    return sum;
}


int solve_03_b(void) {
    char* input = read_file("/Users/juryrazumau/advent_2023/input/03_b.txt");
    char engine[SIZE][SIZE];
    const char *delimiter = "\n";
    char *line = strtok(input, delimiter);
    for (int i = 0; (i < SIZE) && (line != NULL); i++){
        strcpy(engine[i], line);
        line = strtok(NULL, delimiter);
    }
    
    int gears[SIZE][SIZE] = {0};
    int gears_complete[SIZE][SIZE] = {0};
    
    for (int i = 0; i < SIZE; i++){
        int current_number = 0;
        struct point gear = {-1, -1};
        for (int j = 0; j < SIZE; j++){
            if (isdigit(engine[i][j])) {
                current_number = current_number * 10 + engine[i][j] - 48;
                if (gear.x == -1) {
                    gear = find_gear(engine, i, j);
                }
            } else {
                if (gear.x != -1) {
                    int current_value_for_gear = gears[gear.x][gear.y];
                    if (current_value_for_gear) {
                        gears[gear.x][gear.y] *= current_number;
                        gears_complete[gear.x][gear.y] = 1;
                    } else {
                        gears[gear.x][gear.y] = current_number;
                    }
                }
                current_number = 0;
                gear.x = -1;
            }
        }
    }
    int sum = 0;
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            if (gears_complete[i][j]) {
                sum += gears[i][j];
            }
        }
    }
    return sum;
}
