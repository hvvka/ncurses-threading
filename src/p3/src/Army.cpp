//
// Created by Hanna Grodzicka on 02.05.2018.
//

#include "Army.h"
#include "Utility.h"

namespace
{
    constexpr auto ROWS_NUMBER = 6;
} // namespace


Army::Army(army_type army_color) : army_color{army_color}
{
    int x = 0, y = 0;
    std::pair<int, int> position;
    for (int i = 0; i < utility::ARCHERS_COUNT; ++i)
    {
        x = i / ROWS_NUMBER;  // columns
        y = i % ROWS_NUMBER;  // rows
        position = std::make_pair(y, x);
        army.emplace_back(position, army_color);
    }
}

Army::Army(const Army &copy_army) : army_color{copy_army.army_color}, army{copy_army.army}
{}

std::vector<Archer> &Army::get_archers()
{
    return army;
}

int Army::get_score()
{
    return score;
}

army_type Army::get_color()
{
    return army_color;
}

void Army::increase_score()
{
    ++score;
}

void Army::kill_archer(std::vector<Archer>::iterator &archer)
{
    army.erase(archer);
}
