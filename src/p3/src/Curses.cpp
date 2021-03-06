//
// Created by Hanna Grodzicka on 02.05.2018.
//

#include "Curses.h"
#include "Semaphore.h"

#include <thread>
#include <sstream>
#include <random>
#include <unistd.h>

#define HP(hp, c) ((hp)|COLOR_PAIR(c))

namespace
{
    constexpr auto PIF_PAF_DELAY = 900000;
} // namespace

Curses::Curses()
{
    init_ncurses();
    init_colors();
}

void Curses::init_ncurses()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    initscr();
    noecho();
    curs_set(FALSE);
    refresh();
}

void Curses::init_colors()
{
    start_color();
    init_color(COLOR_WHITE, 120, 120, 120);
    init_color(COLOR_RED, 800, 150, 250);
    init_color(COLOR_BLUE, 150, 150, 800);
    init_color(COLOR_CYAN, 150, 150, 330);
    init_color(COLOR_MAGENTA, 330, 150, 150);

    init_pair(1, COLOR_YELLOW, COLOR_WHITE);
    init_pair(2, COLOR_YELLOW, COLOR_WHITE);

    init_pair(3, COLOR_BLACK, COLOR_BLUE);
    init_pair(4, COLOR_YELLOW, COLOR_BLUE);
    init_pair(5, COLOR_GREEN, COLOR_BLUE);

    init_pair(6, COLOR_BLACK, COLOR_RED);
    init_pair(7, COLOR_YELLOW, COLOR_RED);
    init_pair(8, COLOR_GREEN, COLOR_RED);

    init_pair(9, COLOR_BLUE, COLOR_WHITE);
    init_pair(10, COLOR_RED, COLOR_WHITE);
    init_pair(11, COLOR_BLACK, COLOR_BLACK);

    init_pair(12, COLOR_CYAN, COLOR_WHITE);
    init_pair(13, COLOR_MAGENTA, COLOR_WHITE);
}

std::pair<WINDOW *, WINDOW *> Curses::init_windows()
{
    WINDOW *battle_window, *info_window;
    auto max_window_size = get_max_window_size(stdscr);
    battle_window = newwin(max_window_size.first, 3 * max_window_size.second / 4, 0, 0);
    info_window = newwin(max_window_size.first, max_window_size.second / 4, 0, 3 * max_window_size.second / 4);

    wbkgd(battle_window, COLOR_PAIR(1));
    wbkgd(info_window, COLOR_PAIR(2));
    box(battle_window, 0, 0);
    box(info_window, 0, 0);

    return std::make_pair(battle_window, info_window);
}

std::pair<int, int> Curses::get_max_window_size(WINDOW *window)
{
    int max_x, max_y;
    getmaxyx(window, max_y, max_x);
    return std::make_pair(max_y, max_x);
}

void Curses::place_army(std::pair<WINDOW *, WINDOW *> &windows, Army &army)
{
    place_archers(windows.first, army);
    print_score(windows.second, army);
}

void Curses::place_archers(WINDOW *battle_window, Army &army)
{
    auto max_window_size = get_max_window_size(battle_window);
    int x = max_window_size.second / 10;
    if (army.get_color() == army_type::BLUE) x *= 8;  // x offset for painting blue army
    auto coords = std::make_pair(max_window_size.first / 3, x);

    for (auto archer : army.get_archers())
    {
        print_archer(battle_window, coords, archer);
    }
}

void Curses::show_pif_paf(WINDOW *battle_window, int team)
{
    auto max_window_size = get_max_window_size(battle_window);
    int y = max_window_size.first / 2 + rand() % max_window_size.first / 4 - max_window_size.first / 4;
    int x = max_window_size.second / 2 + rand() % max_window_size.second / 5 - max_window_size.first / 5;
    int color = (team == 1) ? 13 : 12;
    wattron(battle_window, COLOR_PAIR(color));
    std::string message = "*pif paf*";
    std::string spaces = "         ";

    Semaphore::lock();
    mvwprintw(battle_window, y, x, message.c_str());
    refresh();
    Semaphore::unlock();

    usleep(PIF_PAF_DELAY);

    Semaphore::lock();
    mvwprintw(battle_window, y, x, spaces.c_str());
    refresh();
    Semaphore::unlock();
}

void Curses::print_archer(WINDOW *battle_window, std::pair<int, int> &coords, Archer &archer)
{
    auto position = archer.get_position();
    int y = coords.first + 2 * position.first;
    int x = coords.second + 4 * position.second;

    int archer_hp = archer.get_health_points();
    auto hp = std::to_string(archer_hp).c_str()[0];  //static_cast<char>(archer_hp + '0');
    int archer_color = get_archer_color_pair(archer);

    mvwaddch(battle_window, y, x, HP(hp, archer_color));
}


int Curses::get_archer_color_pair(Archer &archer)
{
    army_type color = archer.get_army_color();
    int hp = archer.get_health_points();
    if (hp == 0)
    {
        return 11;
    }
    int offset = (color == army_type::BLUE) ? 2 : 5;
    return hp + offset;
}

void Curses::print_score(WINDOW *info_window, Army &army)
{
    auto max_window_size = get_max_window_size(info_window);
    int army_score = army.get_score();

    int color = (army.get_color() == army_type::BLUE) ? 9 : 10;
    int y = (army.get_color() == army_type::BLUE) ? 3 * max_window_size.first / 5 : 2 * max_window_size.first / 5;
    wattron(info_window, COLOR_PAIR(color));

    std::string message = "Score: " + std::to_string(army_score);

    mvwprintw(info_window, y, max_window_size.second / 4, message.c_str());
}

void Curses::end()
{
    getch();
    endwin();
}

void Curses::win_game(WINDOW *battle_window, army_type type)
{
    auto max_window_size = get_max_window_size(battle_window);

    werase(battle_window);
    int color = (type == army_type::RED) ? 10 : 9;
    std::string team = (type == army_type::RED) ? "RED" : "BLUE";
    wattron(battle_window, COLOR_PAIR(color));

    box(battle_window, 0, 0);
    std::string message = "Team " + team + " won!";
    mvwprintw(battle_window, max_window_size.first / 2, max_window_size.second / 2 - message.length() / 2,
              message.c_str());
}
