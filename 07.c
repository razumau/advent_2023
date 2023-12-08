#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <string.h>
#include <ctype.h>

#define HAND_SIZE 5

typedef struct {
    char hand[HAND_SIZE + 1];
    int bid;
} game;

int card_value(char card) {
    if (card == 'T') return 10;
    if (card == 'J') return 11;
    if (card == 'Q') return 12;
    if (card == 'K') return 13;
    if (card == 'A') return 14;
    return card - 48;
}

int compare_ints(const void* a, const void* b)
{
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;

    return (arg1 < arg2) - (arg1 > arg2);
}

int hand_type(const char *hand) {
    int counter[15] = {0};
    for (int i = 0; i < HAND_SIZE + 1; i++) {
        counter[card_value(hand[i])] += 1;
    }
    
    qsort(counter, 15, sizeof(int), compare_ints);
    
    if (counter[0] == 5) return 6;
    if (counter[0] == 4) return 5;
    if (counter[0] == 3) {
        if (counter[1] == 2) {
            return 4;
        } else {
            return 3;
        }
    }
    if (counter[0] == 2) {
        if (counter[1] == 2) {
            return 2;
        } else {
            return 1;
        }
    }
    
    return 0;
}

int compare_hands(const void *a, const void *b) {
    game first = *(const game*)a;
    game second = *(const game*)b;
    
    int first_hand_type = hand_type(first.hand);
    int second_hand_type = hand_type(second.hand);
    
    if (first_hand_type > second_hand_type) return 1;
    if (first_hand_type < second_hand_type) return -1;

    for (int i = 0; i < 5; i++) {
        int first_card_value = card_value(first.hand[i]);
        int second_card_value = card_value(second.hand[i]);
        if (first_card_value > second_card_value) return 1;
        if (first_card_value < second_card_value) return -1;
    }

    return 0;
}

int card_value_with_joker(char card) {
    if (card == 'T') return 10;
    if (card == 'J') return 1;
    if (card == 'Q') return 12;
    if (card == 'K') return 13;
    if (card == 'A') return 14;
    return card - 48;
}

int hand_type_with_joker(const char *hand) {
    int counter[15] = {0};
    for (int i = 0; i < HAND_SIZE + 1; i++) {
        counter[card_value_with_joker(hand[i])] += 1;
    }
    
    int jokers_count = counter[1];
    
    qsort(counter, 15, sizeof(int), compare_ints);
    
    int top_value = (counter[0] == jokers_count) ? counter[1] + jokers_count : counter[0] + jokers_count;
    
    if (top_value >= 5) return 6;
    if (top_value == 4) return 5;
    if (top_value == 3) {
        if (counter[1] == 2) {
            return 4;
        } else {
            return 3;
        }
    }
    if (top_value == 2) {
        if (counter[1] == 2) {
            return 2;
        } else {
            return 1;
        }
    }
    
    return 0;
}

int compare_hands_with_joker(const void *a, const void *b) {
    game first = *(const game*)a;
    game second = *(const game*)b;
    
    int first_hand_type = hand_type_with_joker(first.hand);
    int second_hand_type = hand_type_with_joker(second.hand);
    
    if (first_hand_type > second_hand_type) return 1;
    if (first_hand_type < second_hand_type) return -1;

    for (int i = 0; i < 5; i++) {
        int first_card_value = card_value_with_joker(first.hand[i]);
        int second_card_value = card_value_with_joker(second.hand[i]);
        if (first_card_value > second_card_value) return 1;
        if (first_card_value < second_card_value) return -1;
    }

    return 0;
}

int solve_07(void) {
    int lines_count;
    char **input = readLines("/Users/juryrazumau/advent_2023/input/07_b.txt", &lines_count);
    
    game *games = (game *) malloc(lines_count * sizeof(game));
    
    for (int i = 0; i < lines_count; i++) {
        strncpy(games[i].hand, input[i], HAND_SIZE);
        games[i].bid = atoi(input[i] + HAND_SIZE + 1);
    }
    
    qsort(games, lines_count, sizeof(game), compare_hands);
    
    int winnings = 0;
    
    for (int i = 0; i < lines_count; i++) {
        printf("%d: %d, %s %d\n", i + 1, hand_type(games[i].hand), games[i].hand, games[i].bid);
        winnings += (i + 1) * games[i].bid;
    }
    
    return winnings;
}

int solve_07_b(void) {
    int lines_count;
    char **input = readLines("/Users/juryrazumau/advent_2023/input/07_b.txt", &lines_count);
    
    game *games = (game *) malloc(lines_count * sizeof(game));
    
    for (int i = 0; i < lines_count; i++) {
        strncpy(games[i].hand, input[i], HAND_SIZE);
        games[i].bid = atoi(input[i] + HAND_SIZE + 1);
    }
    
    qsort(games, lines_count, sizeof(game), compare_hands_with_joker);
    
    int winnings = 0;
    
    for (int i = 0; i < lines_count; i++) {
        printf("%d: %d, %s %d\n", i + 1, hand_type_with_joker(games[i].hand), games[i].hand, games[i].bid);
        winnings += (i + 1) * games[i].bid;
    }
    
    return winnings;
}
