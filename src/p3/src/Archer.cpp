//
// Created by Hanna Grodzicka on 02.05.2018.
//

#include "Archer.h"
#include "Semaphore.h"

#include <random>
#include <iostream>

Archer::Archer(std::pair<int, int> position, army_type army_color) : health_points{3}, position{std::move(position)},
                                                                     army_color{army_color}
{}

void Archer::get_shot()
{
    --health_points;
    if (health_points == 0)
    {
//        Semaphore::get_condition_variable().notify_one(); // todo repaint and increase score
    }
}

void Archer::shot_enemy(std::vector<Archer> &enemies)
{
    auto random_enemy_index = rand() % enemies.size();
    auto it = enemies.begin();
    advance(it, random_enemy_index);
    // todo add shot probability
    if (it->get_health_points() > 0)
    {
        it->get_shot();
        std::cout << it->get_position().first << "," << it->get_position().second << " got shot! Health: "
                  << it->get_health_points() << std::endl;
    } else
    {
        std::cout << it->get_position().first << "," << it->get_position().second << " being erased! Health: "
                  << it->get_health_points() << std::endl;
        enemies.erase(it);
        std::cout << "Archers " << enemies.size() << std::endl;
    }
}

int Archer::get_health_points() const
{
    return health_points;
}

std::pair<int, int> Archer::get_position() const
{
    return position;
}

army_type Archer::get_army_color() const
{
    return army_color;
}