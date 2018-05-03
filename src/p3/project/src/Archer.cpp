//
// Created by Hanna Grodzicka on 02.05.2018.
//

#include <utility>
#include "../include/Archer.h"
#include "Semaphore.h"

Archer::Archer(std::pair<int, int> position, army_type army_color) : health_points{3}, position{std::move(position)},
                                                                     army_color{army_color}
{}

void Archer::get_shot()
{
    --health_points;
    if (health_points == 0)
    {
        Semaphore::notify();
        delete this;  // this->~Archer(); ?
    }
}

void Archer::shot_enemy(std::list<Archer>& enemies)
{
    // todo
}

int Archer::get_health_points()
{
    return health_points;
}

std::pair<int, int> Archer::get_position()
{
    return position;
}

army_type Archer::get_army_color()
{
    return army_color;
}