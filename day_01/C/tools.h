#ifndef __TOOLS_H__
#define __TOOLS_H__

typedef struct Rotation {
    char direction;
    int value;
} Rotation;

/**
 * The following function parses a line in the form of "<direction><len>" like R34 or L14 and returns
 * a Rotation struct
 * line -> pointer to line buffer
 */
Rotation parse_line(char * line, ssize_t len);

#endif
