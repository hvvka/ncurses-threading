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
    constexpr auto SHOT_DELAY = 1200000;
} // namespace

Application::Application() : running{true}, army_red{army_type::RED}, army_blue{army_type::BLUE}, ncurses{}
{
    windows = ncurses.init_windows();
    start_threads();
}

void Application::start_threads()
{
    std::thread refresh_thread(&Application::refresh_windows, this, windows.first, windows.second);

    // create archers threads
    std::vector<std::thread> archers_threads;
    for (int i = 0; i < utility::ARCHERS_COUNT; i++)
    {
        archers_threads.emplace_back(&Application::start_archer, this, std::ref(army_red.get_archers()[i]));
        archers_threads.emplace_back(&Application::start_archer, this, std::ref(army_blue.get_archers()[i]));
    }

    refresh_thread.join();

    for (auto &archer_thread : archers_threads)
        archer_thread.join();
}

void Application::refresh_windows(WINDOW *battle_window, WINDOW *info_window)
{
    while (running)
    {
        Semaphore::lock();
        ncurses.place_army(windows, army_red);
        ncurses.place_army(windows, army_blue);
        wrefresh(battle_window);
        wrefresh(info_window);
        Semaphore::unlock();
        usleep(REFRESH_DELAY);
    }
}

void Application::start_archer(Archer &archer)
{
    std::unique_lock<std::mutex> lock(Semaphore::get_mutex());
    while (archer.get_health_points() != 0)
    {
        if (archer.get_army_color() == army_type::RED)
        {
            archer.shot_enemy(army_blue.get_archers());
        } else
        {
            archer.shot_enemy(army_red.get_archers());
        }
        usleep(SHOT_DELAY);
    }

    // todo notify, że zdeh i ma usunąć się z wektora i zaktualizować wynik
//    const auto &tmp = 0;
    // TODO halp
    Semaphore::get_condition_variable().wait(lock, [&]() { return archer.get_health_points() == 0; });
    if (archer.get_army_color() == army_type::RED)
    {
        auto it = std::find(army_red.get_archers().begin(), army_red.get_archers().end(), archer);
        army_red.get_archers().erase(it);
        army_red.increase_score();
    } else
    {
        auto it = std::find(army_blue.get_archers().begin(), army_blue.get_archers().end(), archer);
        army_blue.get_archers().erase(it);
        army_red.increase_score();
    }
}

Application::~Application()
{
    running = false;
    ncurses.end();
}
