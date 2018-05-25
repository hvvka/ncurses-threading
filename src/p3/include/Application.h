//
// Created by Hanna Grodzicka on 02.05.2018.
//

#ifndef ARCHERS_APPLICATION_H
#define ARCHERS_APPLICATION_H

#include "Army.h"
#include "Curses.h"

#include <utility>
#include <condition_variable>

class Application final
{
public:
    Application();

    ~Application();

private:
    bool running;
    Curses ncurses;
    Army army_red;
    Army army_blue;
    std::pair<WINDOW *, WINDOW *> windows;

    void start_threads();

    void refresh_windows();

    void start_archer(Archer &archer);

    void win();
};


#endif //ARCHERS_APPLICATION_H
