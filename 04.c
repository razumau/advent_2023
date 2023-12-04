#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <string.h>
#include <ctype.h>

//#define WINNING_SIZE 5
//#define HAND_SIZE 8
//#define CARDS_COUNT 6

#define WINNING_SIZE 10
#define HAND_SIZE 25
#define CARDS_COUNT 207

int solve_04(void) {
    char* input = read_file("/Users/juryrazumau/advent_2023/input/04_b.txt");
    int sum = 0;
    const char *delimiter = "\n";
    char *line = strtok(input, delimiter);
    
    while (line != NULL) {
        char *winning_start = strchr(line, ':') + 1;
        char *hand_start = strchr(line, '|') + 1;
        int winning[WINNING_SIZE] = {0};
        int hand[HAND_SIZE] = {0};
        int matches = 0;
        
        parse_numbers(winning_start, winning, WINNING_SIZE);
        parse_numbers(hand_start, hand, HAND_SIZE);
        
        for (int i = 0; i < HAND_SIZE; i++) {
            for (int j = 0; j < WINNING_SIZE; j++) {
                if (hand[i] == winning[j]) {
                    matches += 1;
                }
            }
        }
        int points = (matches > 0) ? 1 << (matches - 1) : 0;
        sum += points;
        
        line = strtok(NULL, delimiter);
    }
    
    return sum;
}

int solve_04_b(void) {
    char* input = read_file("/Users/juryrazumau/advent_2023/input/04_b.txt");
    const char *delimiter = "\n";
    char *line = strtok(input, delimiter);
    int sum = 0;
    int matches[CARDS_COUNT + 1] = {0};
    int copies[CARDS_COUNT + 1] = {0};
    for (int i = 1; i <= CARDS_COUNT; i++) {
        copies[i] = 1;
    }
    int card_count = 1;
    
    while (line != NULL) {
        char *winning_start = strchr(line, ':') + 1;
        char *hand_start = strchr(line, '|') + 1;
        int winning[WINNING_SIZE] = {0};
        int hand[HAND_SIZE] = {0};
        int match_count = 0;
        
        parse_numbers(winning_start, winning, WINNING_SIZE);
        parse_numbers(hand_start, hand, HAND_SIZE);
        
        for (int i = 0; i < HAND_SIZE; i++) {
            for (int j = 0; j < WINNING_SIZE; j++) {
                if (hand[i] == winning[j]) {
                    match_count += 1;
                }
            }
        }
        matches[card_count] += match_count;
        card_count += 1;
        
        line = strtok(NULL, delimiter);
    }
    
    for (int i = 1; i <= CARDS_COUNT; i++) {
        printf("current state is %d %d %d %d %d %d %d\n", copies[0], copies[1],copies[2], copies[3],copies[4], copies[5], copies[6]);
        printf("looking at card %d\n", i);
        int copies_to_add = copies[i];
        for (int j = 0; (j < matches[i]) && (i + j <= CARDS_COUNT); j++) {
            printf("adding %d copies of %d\n", copies_to_add, i + j + 1);
            copies[i + j + 1] += copies_to_add;
        }
    }
    
    printf("final state is %d %d %d %d %d %d %d\n", copies[0], copies[1],copies[2], copies[3],copies[4], copies[5], copies[6]);
    
    for (int i = 1; i <= CARDS_COUNT; i++) {
        sum += copies[i];
    }
    
    return sum;
}
