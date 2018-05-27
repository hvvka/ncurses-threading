//
// Created by Hanna Grodzicka on 02.05.2018.
//

#include "Application.h"
#include "Semaphore.h"
#include "Utility.h"

#include <thread>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <random>

namespace
{
    constexpr auto REFRESH_DELAY = 60000;
    constexpr auto SHOT_DELAY = 100000;
} // namespace

Application::Application() : running{true}, ncurses{}, army_red{army_type::RED}, army_blue{army_type::BLUE}
{
    windows = ncurses.init_windows();
    start_threads();
}

void Application::start_threads()
{
    std::thread refresh_thread(&Application::refresh_windows_periodically, this);
    std::thread win_thread(&Application::win, this);
    std::thread random_number_thread(&Application::generate_random_number, this);
    std::thread show_pif_paf_thread(&Application::show_pif_paf, this);

    // create archers' threads
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

    show_pif_paf_thread.join();
    random_number_thread.join();
    win_thread.join();
    refresh_thread.join();
}

void Application::refresh_windows_periodically()
{
    while (running)
    {
        usleep(REFRESH_DELAY);
        std::unique_lock<std::mutex> lock(Semaphore::get_mutex());
        refresh_windows();
    }
}

void Application::refresh_windows()
{
    ncurses.place_army(windows, army_red);
    ncurses.place_army(windows, army_blue);
    wrefresh(windows.first);
    wrefresh(windows.second);
}

void Application::start_archer(Archer &archer)
{
    std::vector<Archer> &archers_army =
            archer.get_army_color() == army_type::BLUE ? army_blue.get_archers() : army_red.get_archers();
    auto predicate = [&archer](const Archer &record) {
        return archer.get_position() == record.get_position() &&
               archer.get_health_points() == record.get_health_points() &&
               archer.get_army_color() == record.get_army_color();
    };

    while (std::find_if(std::begin(archers_army), std::end(archers_army), predicate) != std::end(archers_army) &&
           !army_blue.get_archers().empty() && !army_red.get_archers().empty())
    {
        Semaphore::wait();
        std::unique_lock<std::mutex> lock(Semaphore::get_mutex());
        if (archer.get_army_color() == army_type::RED)
        {
            pif_paf = 1;
            Semaphore::get_condition_variable().notify_all();
            auto it = archer.shot_enemy(army_blue.get_archers(), random_number);
            if (it != army_blue.get_archers().end())
            {
                ncurses.place_army(windows, army_blue);
                army_blue.kill_archer(it);
                army_red.increase_score();
            }
        } else  // blue
        {
            pif_paf = 2;
            Semaphore::get_condition_variable().notify_all();
            auto it = archer.shot_enemy(army_red.get_archers(), random_number);
            if (it != army_red.get_archers().end())
            {
                ncurses.place_army(windows, army_red);
                army_red.kill_archer(it);
                army_blue.increase_score();
            }
        }
    }
}

void Application::generate_random_number()
{
    unsigned long long int random_value = 0;
    size_t size = sizeof(random_value);
    std::ifstream urandom("/dev/urandom", std::ios::in | std::ios::binary);
    if (urandom)
    {
        while (running)
        {
            usleep(SHOT_DELAY);
            urandom.read(reinterpret_cast<char *>(&random_value), size);
            if (urandom)
            {
                random_number = random_value % 100;
            } else  // Reading failure
            {
                random_number = rand() % 100;
            }
            Semaphore::notify();
        }
        urandom.close();
    } else
    {
        std::cerr << "Failed to open /dev/urandom" << std::endl;
    }
}

void Application::show_pif_paf()
{
    while (running)
    {
        {
            std::unique_lock<std::mutex> lock(Semaphore::get_mutex());
            Semaphore::get_condition_variable().wait(lock, [this] { return pif_paf != 0; });
        }
        ncurses.show_pif_paf(windows.first, pif_paf);
        pif_paf = 0;
    }
}

void Application::win()
{
    std::unique_lock<std::mutex> lock(Semaphore::get_mutex());
    Semaphore::get_condition_variable().wait(lock, [this] {
        if (army_red.get_archers().empty())
        {
            ncurses.win_game(windows.first, army_blue.get_color());
            return true;
        } else if (army_blue.get_archers().empty())
        {
            ncurses.win_game(windows.first, army_red.get_color());
            return true;
        }
        return false;
    });
    running = false;
    army_blue.get_archers().clear();
    army_red.get_archers().clear();
    refresh_windows();
    ncurses.end();
}

Application::~Application()
{
    ncurses.end();
    running = false;
}
