//
// Created by Hanna Grodzicka on 02.05.2018.
//

#include "Archer.h"
#include "Semaphore.h"
#include <random>

Archer::Archer(std::pair<int, int> position, army_type army_color) : health_points{3}, position{std::move(position)},
                                                                     army_color{army_color}
{}

void Archer::get_shot()
{
    --health_points;
    if (health_points == 0)
    {
        Semaphore::get_condition_variable().notify_one(); // todo repaint and increase score
    }
}

void Archer::shot_enemy(std::vector<Archer> &enemies)
{
    auto random_enemy_index = rand() % enemies.size();
    auto it = enemies.begin();
    advance(it, random_enemy_index);
    // todo add shot probability
    it->get_shot();
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