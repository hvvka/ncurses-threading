//
// Created by Hanna Grodzicka on 02.05.2018.
//

#include "Army.h"

#define ARCHERS_COUNT 24
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
        army.push_back(*new Archer(position, army_color));
    }
}

std::list<Archer> Army::get_army() //todo return reference
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


