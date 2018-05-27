//
// Created by Hanna Grodzicka on 02.05.2018.
//

#ifndef ARCHERS_APPLICATION_H
#define ARCHERS_APPLICATION_H

#include "Army.h"
#include "Curses.h"

#include <utility>
#include <condition_variable>
#include <atomic>

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
    std::atomic<int> random_number{};
    int pif_paf{0};

    void start_threads();

    void refresh_windows_periodically();

    void refresh_windows();

    void start_archer(Archer &archer);

    void generate_random_number();

    void show_pif_paf();

    void win();
};


#endif //ARCHERS_APPLICATION_H
