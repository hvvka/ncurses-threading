//
// Created by Hanna Grodzicka on 02.05.2018.
//

#include "Application.h"
#include "Semaphore.h"
#include "Utility.h"

#include <thread>
#include <unistd.h>
#include <iostream>

namespace
{
    constexpr auto REFRESH_DELAY = 60000;
    constexpr auto SHOT_DELAY = 2000000;
} // namespace

Application::Application() : running{true}, army_red{army_type::RED}, army_blue{army_type::BLUE}
//, ncurses{}
{
//    windows = ncurses.init_windows();
    start_threads();
}

void Application::start_threads()
{
//    std::thread refresh_thread(&Application::refresh_windows, this, windows.first, windows.second);
    std::thread win_red_thread(&Application::win_red, this);
    std::thread win_blue_thread(&Application::win_blue, this);

    // create archers threads
    std::vector<std::thread> archers_threads;
    archers_threads.reserve(utility::ARCHERS_COUNT * 2);
    for (int i = 0; i < utility::ARCHERS_COUNT; i++)
    {
        archers_threads.emplace_back(&Application::start_archer, this, std::ref(army_red.get_archers()[i]));
//        archers_threads.emplace_back(&Application::start_archer, this, std::ref(army_blue.get_archers()[i]));
    }

    for (auto &archer_thread : archers_threads)
    {
        archer_thread.join();
        std::cout << "Archer thread DIED" << std::endl;
    }

//    army_red.get_archers().clear();
//    army_blue.get_archers().clear();
    Semaphore::get_condition_variable().notify_one();

    win_blue_thread.join();
    win_red_thread.join();

//    refresh_thread.join();
}

// todo delete passing windows
void Application::refresh_windows(WINDOW *battle_window, WINDOW *info_window)
{
    while (running)
    {
        Semaphore::lock();
//        ncurses.place_army(windows, army_red);
//        ncurses.place_army(windows, army_blue);
        wrefresh(battle_window);
        wrefresh(info_window);
        Semaphore::unlock();
        usleep(REFRESH_DELAY);
    }
}

void Application::start_archer(Archer &archer)
{
    Army &opponent_army = archer.get_army_color() == army_type::BLUE ? army_red : army_blue;
    while (archer.get_health_points() != 0 && !opponent_army.get_archers().empty())
    {
        usleep(SHOT_DELAY);
        std::unique_lock<std::mutex> lock(Semaphore::get_mutex());
        std::cout << archer.get_position().first << "," << archer.get_position().second << " shooting" << std::endl;
        if (archer.get_army_color() == army_type::RED)
        {
            archer.shot_enemy(army_blue.get_archers());
        } else
        {
            archer.shot_enemy(army_red.get_archers());
        }
    }

    std::cout << "zdycham " << archer.get_position().first << "," << archer.get_position().second << std::endl;

    // todo kill winners manually, so that their thread ended

//    std::unique_lock<std::mutex> lock(Semaphore::get_mutex());
    // todo notify, że zdeh i ma usunąć się z wektora i zaktualizować wynik
//    Semaphore::get_condition_variable().wait(lock, [&archer]() { return archer.get_health_points() == 0; });

//    auto predicate = [&archer](const Archer &record) {
//        return archer.get_position() == record.get_position() &&
//               archer.get_health_points() == record.get_health_points() &&
//               archer.get_army_color() == record.get_army_color();
//    };

    if (archer.get_army_color() == army_type::RED)
    {
        // todo check if find_if != archers.end()
//        auto it = std::find_if(army_red.get_archers().begin(), army_red.get_archers().end(), predicate);
//        army_red.get_archers().erase(it);
        army_red.increase_score();
        std::cout << "Red score: " << army_red.get_score() << std::endl;
    } else
    {
//        auto it = std::find_if(army_blue.get_archers().begin(), army_blue.get_archers().end(), predicate);
//        army_blue.get_archers().erase(it);
        army_blue.increase_score();
        std::cout << "Blue score: " << army_blue.get_score() << std::endl;
    }
}

Application::~Application()
{
    running = false;
//    ncurses.end();
}

void Application::win_red()
{
    while (running)
    {
        std::unique_lock<std::mutex> lock(Semaphore::get_mutex());
        Semaphore::get_condition_variable().wait(lock, [this] { return army_red.get_archers().empty(); });
//        ncurses.win_game(windows.first, army_red.get_color());
    }
}

void Application::win_blue()
{
    while (running)
    {
        std::unique_lock<std::mutex> lock(Semaphore::get_mutex());
        Semaphore::get_condition_variable().wait(lock, [this] { return army_blue.get_archers().empty(); });
//        ncurses.win_game(windows.first, army_red.get_color());
    }
}
