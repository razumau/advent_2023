#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <string.h>
#include <ctype.h>

int is_possible(char *game) {
    for (int i = 0; i < strlen(game); i++) {
        if (isdigit(game[i])) {
            long count = strtol(game + i, NULL, 10);
            int max = 0;
            char *color_start = strchr(game + i, ' ');
            switch (color_start[1]) {
                case 'r':
                    max = 12;
                    break;
                case 'g':
                    max = 13;
                    break;
                case 'b':
                    max = 14;
                    break;
            }
            if (count > max) { return 0; }
        }
    }
    return 1;
}

long fewest_cubes(char *game) {
    long blue = 0, red = 0, green = 0;
    for (int i = 0; i < strlen(game); i++) {
        if (isdigit(game[i])) {
            long count = strtol(game + i, NULL, 10);
            char *color_start = strchr(game + i, ' ');
            switch (color_start[1]) {
                case 'r':
                    red = (count > red) ? count : red;
                    break;
                case 'g':
                    green = (count > green) ? count : green;
                    break;
                case 'b':
                    blue = (count > blue) ? count : blue;
                    break;
            }
        }
    }
    return blue * red * green;
}

int solve_02(void) {
    char* input = read_file("/Users/juryrazumau/advent_2023/input/02_b.txt");
    const char *delimiter = "\n";
    char *line = strtok(input, delimiter);
    int sum = 0;
    while (line != NULL) {
        char *space = strchr(line, ' ');
        long game_id = strtol(space, NULL, 10);
        
        char *colon = strchr(line, ':');
        if (is_possible(colon + 2)) {
            sum += game_id;
        }
        line = strtok(NULL, delimiter);
    }
    return sum;
}




long solve_02_b(void) {
    char* input = read_file("/Users/juryrazumau/advent_2023/input/02_b.txt");
    const char *delimiter = "\n";
    char *line = strtok(input, delimiter);
    long sum = 0;
    while (line != NULL) {
        char *colon = strchr(line, ':');
        sum += fewest_cubes(colon + 2);
        line = strtok(NULL, delimiter);
    }
    return sum;
}
