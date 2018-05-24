//
// Created by Hanna Grodzicka on 02.05.2018.
//

#include "Application.h"
#include "Semaphore.h"
#include "Utility.h"

#include <thread>
#include <unistd.h>

namespace
{
    constexpr auto REFRESH_DELAY = 60000;
    constexpr auto SHOT_DELAY = 1000000;
} // namespace

Application::Application() : running{true}, ncurses{}, army_red{army_type::RED}, army_blue{army_type::BLUE}
{
    windows = ncurses.init_windows();
    start_threads();
}

void Application::start_threads()
{
    std::thread refresh_thread(&Application::refresh_windows, this);
    std::thread win_red_thread(&Application::win_red, this);
    std::thread win_blue_thread(&Application::win_blue, this);

    // create archers threads
    std::vector<std::thread> archers_threads;
    archers_threads.reserve(utility::ARCHERS_COUNT * 2);
    for (int i = 0; i < utility::ARCHERS_COUNT; i++)
    {
        archers_threads.emplace_back(&Application::start_archer, this, std::ref(army_red.get_archers()[i]));
        archers_threads.emplace_back(&Application::start_archer, this, std::ref(army_blue.get_archers()[i]));
    }

    for (auto &archer_thread : archers_threads)
    {
        archer_thread.join();
    }

    Semaphore::get_condition_variable().notify_one();

    win_blue_thread.join();
    win_red_thread.join();

    refresh_thread.join();
}

void Application::refresh_windows()
{
    while (running)
    {
        usleep(REFRESH_DELAY);
        std::unique_lock<std::mutex> lock(Semaphore::get_mutex());
        ncurses.place_army(windows, army_red);
        ncurses.place_army(windows, army_blue);
        wrefresh(windows.first);
        wrefresh(windows.second);
    }
}

void Application::start_archer(Archer &archer)
{
    Army &opponent_army = archer.get_army_color() == army_type::BLUE ? army_red : army_blue;
    while (archer.get_health_points() > 0 && !opponent_army.get_archers().empty())
    {
        usleep(SHOT_DELAY);
        std::unique_lock<std::mutex> lock(Semaphore::get_mutex());
        if (archer.get_army_color() == army_type::RED)
        {
            if (archer.shot_enemy(army_blue.get_archers()))
                army_red.increase_score();
        } else
        {
            if (archer.shot_enemy(army_red.get_archers()))
                army_blue.increase_score();
        }
    }

    if (opponent_army.get_archers().empty())
    {
        army_blue.get_archers().clear();
        army_red.get_archers().clear();
    }
}

Application::~Application()
{
    running = false;
    ncurses.end();
}

void Application::win_red()
{
    while (running)
    {
        std::unique_lock<std::mutex> lock(Semaphore::get_mutex());
        Semaphore::get_condition_variable().wait(lock, [this] { return army_red.get_archers().empty(); });
        ncurses.win_game(windows.first, army_red.get_color());
    }
}

void Application::win_blue()
{
    while (running)
    {
        std::unique_lock<std::mutex> lock(Semaphore::get_mutex());
        Semaphore::get_condition_variable().wait(lock, [this] { return army_blue.get_archers().empty(); });
        ncurses.win_game(windows.first, army_red.get_color());
    }
}
