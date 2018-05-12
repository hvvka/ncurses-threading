//
// Created by Hanna Grodzicka on 02.05.2018.
//

#include "Army.h"

#define ARCHERS_COUNT 1  // TODO change back to 24
#define ROWS_NUMBER 6

Army::Army(army_type army_color) : army_color{army_color}, score{0}
{
    int x = 0, y = 0;
    std::pair<int, int> position;
    for (int i = 0; i < ARCHERS_COUNT; ++i)
    {
        x = i / ROWS_NUMBER;  // columns
        y = i % ROWS_NUMBER;  // rows
        position = std::make_pair(y, x);
        army.emplace_back(position, army_color);
    }
}

std::vector <Archer> &Army::get_archers()
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


