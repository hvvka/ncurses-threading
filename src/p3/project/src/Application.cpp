//
// Created by Hanna Grodzicka on 02.05.2018.
//

#include "Application.h"
#include "Semaphore.h"
#include <thread>
#include <unistd.h>

#define DELAY 60000

Application::Application() : running{true}, army_red{RED}, army_blue{BLUE}, ncurses{}
{
    start_threads();
}

void Application::start_threads()
{
    auto windows = ncurses.init_windows();

    std::thread refresh_thread(&Application::refresh_windows, this, windows.first, windows.second);

    ncurses.place_army(windows, army_red);
    ncurses.place_army(windows, army_blue);

    refresh_thread.join();
}

void Application::refresh_windows(WINDOW *battle_window, WINDOW *info_window)
{
    while (running)
    {
        Semaphore::lock();
        wrefresh(battle_window);
        wrefresh(info_window);
        Semaphore::unlock();
    }
    usleep(DELAY);
}

Application::~Application()
{
    running = false;
    ncurses.end();
}