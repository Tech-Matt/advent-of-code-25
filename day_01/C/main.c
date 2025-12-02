#include <stdio.h>
#include <stdlib.h>
#include "tools.h"

int main() {
    // File opening variables
    FILE *fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t n_chars;

    // open the file
    fp = fopen("../data.txt", "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    // This keeps track of the currently pointed value from the rotations
    int sum = 0;
    // this one insteads keeps track of how many times the count has reached the value '0'
    int n_zeros = 0;

    while ((n_chars = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length: %zu:\n", n_chars);
        printf("%s", line);
        Rotation current_rot = parse_line(line, n_chars);
        // Code logic
        if (current_rot.direction == 'L') {
            sum -= current_rot.value;
        }
        else if (current_rot.direction == 'R') {
            sum += current_rot.value;
        }
        else {
            printf("\nInvalid direction: %c", current_rot.direction);
            exit(EXIT_FAILURE);
        }

        // Check how many zeros
        if (sum == 0)
            n_zeros++;
    }

    // Printing result
    printf("\nFINAL RESULT: %d", n_zeros);

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}
