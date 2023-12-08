#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <string.h>
#include <ctype.h>

typedef struct {
    long destination;
    long source;
    long range;
} map;

long follow_map(long start, map map) {
    if (start >= map.source && start <= map.source + map.range) {
        return start - map.source + map.destination;
    } else {
        return -1;
    }
}

long long go_backwards(long long finish, map map) {
    if (finish >= map.destination && finish <= map.destination + map.range) {
        return finish - map.destination + map.source;
    } else {
        return -1;
    }
}

int is_in_seeds(long long *seeds, int seeds_count, long long value) {
    for (int i = 0; i < seeds_count - 1; i += 2) {
        if (value >= seeds[i] && value <= seeds[i] + seeds[i + 1]) {
            return 1;
        }
    }
    return 0;
}

int solve_05(void) {
    char* input = read_file("/Users/juryrazumau/advent_2023/input/05_b.txt");
    const char *delimiter = "\n";
    char *line = strtok(input, delimiter);
    
    long seeds[50] = {0};
    uint transferred[50] = {0};
    parse_all_numbers(line + 6, seeds);
    line = strtok(NULL, delimiter);
    uint seeds_count = 1;
    while (seeds[seeds_count] > 0) { seeds_count += 1; }
    
    while (line != NULL) {
        if (strlen(line) == 0) { continue; }
        if (isdigit(line[0])) {
            long numbers[3];
            parse_numbers(line, numbers, 3);
            map map = {numbers[0], numbers[1], numbers[2]};
            
            for (uint i = 0; i < seeds_count; i++) {
                if (transferred[i]) { continue; }
                long destination = follow_map(seeds[i], map);
                if (destination != -1) {
                    transferred[i] = 1;
                    seeds[i] = destination;
                }
            }
        } else {
            for (uint i = 0; i < seeds_count; i++) {
                transferred[i] = 0;
            }
        }
        line = strtok(NULL, delimiter);
    }
    
    printf("final locations are\n");
    for (uint i = 0; i < seeds_count; i++) {
        printf("%ld\n", seeds[i]);
    }
    
    long min = seeds[0];
    for (uint i = 1; i < seeds_count; i++) {
        min = seeds[i] < min ? seeds[i] : min;
    }
    
    return min;
}

long long find_image(long long final_location, char **input, int lines_count) {
    uint moved = 0;
    long long location = final_location;
    char *line;
    for (int i = lines_count - 1; i >= 0; i--) {
        line = input[i];
        if (strlen(line) == 0) { continue; }

        if (isdigit(line[0])) {
            if (moved) { continue; }

            long numbers[3];
            parse_numbers(line, numbers, 3);
            map map = {numbers[0], numbers[1], numbers[2]};
            
            long long new_location = go_backwards(location, map);
            if (new_location != -1) {
                moved = 1;
//                printf("moved from %lld to %lld\n", location, new_location);
                location = new_location;
            }
        } else {
            moved = 0;
        }
    }
    return location;
}

int solve_05_b(void) {
    int lines_count;
    char **input = readLines("/Users/juryrazumau/advent_2023/input/05_b.txt", &lines_count);
    
    long long seeds[50] = {0};
    parse_all_numbers(input[0] + 6, seeds);
    uint seeds_count = 1;
    while (seeds[seeds_count] > 0) { seeds_count += 1; }
    
    long long result = 0;
    
    for (long long i = 100000000; i < 219529183; i++) {
        long long image = find_image(i, input, lines_count);
        int found = is_in_seeds(seeds, seeds_count, image);
        
        if (i % 100000 == 0) { printf("%lld\n", i); }
        if (found) {
            printf("%lld, %lld, %d\n", i, image, found);
            result = i;
            break;
        }
    }
    
    return result;
}

// from 0 to 10000000 is empty
// from 10000000 to 100000000 is empty
// from 100000000 to 220000000 we found 220000000 (in 1000000 steps)
// but 219529183 is too high (so the answer is below 219000000)
/// and 100000000 is too low
/// but found nothing between 100000000 and 219529183
