//
// Created by Hanna Grodzicka on 02.05.2018.
//

#include <utility>
#include "../include/Archer.h"
#include "Semaphore.h"
#include <random>

Archer::Archer(std::pair<int, int> position, army_type army_color) : health_points{3}, position{std::move(position)},
                                                                     army_color{army_color}
{}

bool Archer::get_shot()
{
    --health_points;
    if (health_points == 0)
    {
        Semaphore::notify();  // todo repaint and increase score
        return true;
    }
    return false;
}

void Archer::shot_enemy(std::vector <Archer> &enemies)
{
    unsigned long random_enemy_index = rand() % enemies.size();
    auto it = enemies.begin();
    advance(it, random_enemy_index);
    if (it->get_shot())
        enemies.erase(it);  // todo why the enemy is no erased
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