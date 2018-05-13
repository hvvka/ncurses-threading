//
// Created by Hanna Grodzicka on 15.04.2018.
//

#ifndef TETRIS_SHAPE_H
#define TETRIS_SHAPE_H

#include <ncurses.h>

#define EMPTY_BLOCK " "
#define FULL_BLOCK(x) (' '|COLOR_PAIR(x))

enum block_type
{
    L = 1,
    O = 2,
    S = 3,
    T = 4
};

struct block
{
    int x;
    int y;
    block_type type;
};

void paint(WINDOW *w, block_type type, int y, int x);

void clean(WINDOW *w, block_type type, int y, int x);

#endif //TETRIS_SHAPE_H
