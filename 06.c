#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <string.h>
#include <ctype.h>

#define RACES_COUNT 4

int can_win(int time, int holding_time, long distance) {
    long long speed = holding_time;
    long long distance_traveled = (time - holding_time) * speed;
    return distance_traveled > distance;
}

int ways_to_win(int time, long distance) {
    int count = 0;
    for (int i = 0; i < time; i++) {
        if (can_win(time, i, distance)) {
            count += 1;
        }
    }
    return count;
}

int solve_06(void) {
    int _lines_count;
    char **input = readLines("/Users/juryrazumau/advent_2023/input/06_b.txt", &_lines_count);
    int times[RACES_COUNT] = {0};
    int distances[RACES_COUNT] = {0};
    parse_numbers(input[0] + 10, times, RACES_COUNT);
    parse_numbers(input[1] + 10, distances, RACES_COUNT);

    int result = 1;
    
    for (int i = 0; i < RACES_COUNT; i++) {
        int ways = ways_to_win(times[i], distances[i]);
        printf("ways to win for time %d and distance %d: %d\n", times[i], distances[i], ways);
        result *= ways;
    }
    
    return result;
}

int solve_06_b(void) {
    return ways_to_win(48876981, 255128811171623);
}
