#include <stdio.h>
#include <stdlib.h>
#include "tools.h"

Rotation parse_line(char *line, ssize_t len) {
    if (line == NULL) {
       printf("\nLine is empty or missing");
       exit(EXIT_FAILURE);
    }

    // Get the data
    char direction = line[0];
    char *rotations = malloc(len-1); // first char doesn't go in here so -1
    int i = 1;
    while(i < len-1) { // we reach the len-1 to exclude the newline char
        rotations[i] = line[i];
        i++;
    }
    rotations[i] = '\0';

    // convert to integer
    int rotation_value = atoi(rotations);

    // Create and return Rotation struct
    Rotation result;
    result.direction = direction;
    result.value = rotation_value;

    // Free memory
    free(rotations);

    return result;
}
