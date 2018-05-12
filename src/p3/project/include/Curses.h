//
// Created by Hanna Grodzicka on 02.05.2018.
//

#ifndef ARCHERS_NCURSES_H
#define ARCHERS_NCURSES_H

#include "Army.h"

#include <ncurses.h>
#include <utility>

class Curses
{
private:
    void init_ncurses();
    void init_colors();

    void place_archers(WINDOW *battle_window, Army &army);

    void print_archer(WINDOW *battle_window, std::pair<int, int> coords, Archer &archer);

    int get_archer_color_pair(Archer &archer);

    void print_score(WINDOW *info_window, Army &army);

public:
    Curses();
    virtual ~Curses() = default;
    std::pair<int, int> get_max_window_size(WINDOW* window);
    std::pair<WINDOW*, WINDOW*> init_windows();

    void place_army(std::pair<WINDOW *, WINDOW *> windows, Army &army);
    void end();
};


#endif //ARCHERS_NCURSES_H
