#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <string.h>
#include <ctype.h>

typedef struct {
    char head[4];
    char left[4];
    char right[4];
} node;


int solve_08(void) {
    int lines_count;
    char **input = readLines("/Users/juryrazumau/advent_2023/input/08_b.txt", &lines_count);
    char *path = input[0];
    
    node *nodes = (node *) malloc(lines_count * sizeof(node));
    
    for (int i = 2; i < lines_count; i++) {
        strncpy(nodes[i - 2].head, input[i], 3);
        strncpy(nodes[i - 2].left, input[i] + 7, 3);
        strncpy(nodes[i - 2].right, input[i] + 12, 3);
    }
    
    char *current = "AAA";
    uint steps = 0;
    
    while (strcmp(current, "ZZZ")) {
        char turn = path[steps % strlen(path)];
        printf("%d: turning %c\n", steps, turn);
        node next_node;
        for (int i = 0; i < lines_count; i++) {
            if (!strcmp(nodes[i].head, current)) {
                next_node = nodes[i];
                printf("found %s %s %s\n", next_node.head, next_node.left, next_node.right);
                break;
            }
        }
        if (turn == 'R') {
            current = next_node.right;
        } else {
            current = next_node.left;
        }
        printf("going to %s\n", current);
        steps += 1;
    }
    
    return steps;
}

#define PARALLEL_NODES 6

int found_all_loops(long long* loops) {
    for (int i = 0; i < PARALLEL_NODES; i++) {
        if (!loops[i]) return 0;
    }
    return 1;
}

int solve_08_b(void) {
    int lines_count;
    char **input = readLines("/Users/juryrazumau/advent_2023/input/08_b.txt", &lines_count);
    
    char *path = input[0];
    
    node *nodes = (node *) malloc(lines_count * sizeof(node));
    for (int i = 2; i < lines_count; i++) {
        strncpy(nodes[i - 2].head, input[i], 3);
        strncpy(nodes[i - 2].left, input[i] + 7, 3);
        strncpy(nodes[i - 2].right, input[i] + 12, 3);
    }
    
//    char* current[PARALLEL_NODES] = {"11A", "22A"};
    char* current[PARALLEL_NODES] = {"DVA", "VPA", "AAA", "VBA", "DTA", "TVA"};
    uint steps = 0;
    
    int zs[PARALLEL_NODES][1000] = {0};
    long long first[PARALLEL_NODES] = {0};
    long long diffs[PARALLEL_NODES] = {0};
    
    while (!found_all_loops(first)) {
        char turn = path[steps % strlen(path)];
        
        for (int i = 0; i < PARALLEL_NODES; i++) {
            uint next_node = -1;
            for (int j = 0; j < lines_count; j++) {
                if (!strcmp(nodes[j].head, current[i])) {
                    next_node = j;
                    break;
                }
            }
            if (turn == 'R') {
                current[i] = nodes[next_node].right;
            } else {
                current[i] = nodes[next_node].left;
            }
            if (current[i][2] == 'Z') {
                if (zs[i][next_node]) {
                    printf("step %d\n", steps);
                    printf("current is %s\n", current[i]);
                    printf("%d has already been at %d on step %d\n", i, next_node, zs[i][next_node]);
                    if (!first[i]) {
                        first[i] = zs[i][next_node];
                        diffs[i] = steps - zs[i][next_node];
                    }
                    printf("diff for %d is %d\n", i, steps - zs[i][next_node]);
                }

                zs[i][next_node] = steps;
            }
        }
        steps += 1;
    }
    
    for (int i = 0; i < PARALLEL_NODES; i++) {
        printf("for %d: first at %d, step %d\n", i, first[i], diffs[i]);
    }

    
    int found = 1;
    for (long long i = 1; ; i++) {
        long long value = first[PARALLEL_NODES - 1] + (i * diffs[PARALLEL_NODES - 1]);
        for (int j = 0; j < PARALLEL_NODES - 1; j++) {
            if ((value - first[j]) % diffs[j] != 0) {
                found = 0;
                break;
            }
        }
//        if (i % 100000 == 0) {printf("%lld\n", i);}
        if (found) {
            printf("value: %lld, i: %lld\n", value, i);
            break;
        } else {
            found = 1;
        }
    }
    
    return steps;
}
// 14590000 too low
// 112200000 too low
// 190100000 too low
// 526000000 is wrong
// 226304959

