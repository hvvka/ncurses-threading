//
// Created by Hanna Grodzicka on 15.04.2018.
//

#include "Block.h"

#include <cstdio>
#include <cstdlib>
#include <cstdbool>
#include <cstring>
#include <ctime>

//namespace {
//    constexpr const char* EMPTY_BLOCK = " ";
//    constexpr const char* FULL_BLOCK = "X";
//}

void paint(WINDOW *w, block_type type, int y, int x)
{
    switch (type)
    {
        case block_type::L:
            mvwaddch(w, y, x, FULL_BLOCK(5));
            mvwaddch(w, y + 1, x, FULL_BLOCK(5));
            mvwaddch(w, y + 2, x, FULL_BLOCK(5));
            mvwaddch(w, y + 2, x + 1, FULL_BLOCK(5));
            break;
        case block_type::O:
            mvwaddch(w, y, x, FULL_BLOCK(6));
            mvwaddch(w, y, x + 1, FULL_BLOCK(6));
            mvwaddch(w, y + 1, x + 1, FULL_BLOCK(6));
            mvwaddch(w, y + 1, x, FULL_BLOCK(6));
            break;
        case block_type::S:
            mvwaddch(w, y, x, FULL_BLOCK(7));
            mvwaddch(w, y + 1, x, FULL_BLOCK(7));
            mvwaddch(w, y + 1, x + 1, FULL_BLOCK(7));
            mvwaddch(w, y + 2, x + 1, FULL_BLOCK(7));
            break;
        case block_type::T:
            mvwaddch(w, y, x, FULL_BLOCK(8));
            mvwaddch(w, y + 1, x, FULL_BLOCK(8));
            mvwaddch(w, y, x + 1, FULL_BLOCK(8));
            mvwaddch(w, y, x - 1, FULL_BLOCK(8));
            break;
    }
}

void clean(WINDOW *w, block_type type, int y, int x)
{
    switch (type)
    {
        case block_type::L:
            mvwprintw(w, y + 1, x, EMPTY_BLOCK);
            mvwprintw(w, y + 2, x, EMPTY_BLOCK);
            mvwprintw(w, y + 2, x + 1, EMPTY_BLOCK);
            break;
        case block_type::O:
            mvwprintw(w, y, x + 1, EMPTY_BLOCK);
            mvwprintw(w, y + 1, x + 1, EMPTY_BLOCK);
            mvwprintw(w, y + 1, x, EMPTY_BLOCK);
            break;
        case block_type::S:
            mvwprintw(w, y + 1, x, EMPTY_BLOCK);
            mvwprintw(w, y + 1, x + 1, EMPTY_BLOCK);
            mvwprintw(w, y + 2, x + 1, EMPTY_BLOCK);
            break;
        case block_type::T:
            mvwprintw(w, y + 1, x, EMPTY_BLOCK);
            mvwprintw(w, y, x + 1, EMPTY_BLOCK);
            mvwprintw(w, y, x - 1, EMPTY_BLOCK);
            break;
    }
    mvwprintw(w, y, x, EMPTY_BLOCK);
}
