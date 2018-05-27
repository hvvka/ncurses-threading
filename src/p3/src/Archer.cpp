//
// Created by Hanna Grodzicka on 02.05.2018.
//

#include "Archer.h"
#include "Semaphore.h"

#include <random>

namespace
{
    constexpr auto SHOT_PROBABILITY = 55;
} // namespace

Archer::Archer(std::pair<int, int> position, army_type army_color) : position{std::move(position)},
                                                                     army_color{army_color}
{}

void Archer::get_shot()
{
    --health_points;
}

std::vector<Archer>::iterator Archer::shot_enemy(std::vector<Archer> &enemies, int shot_chance)
{
    if (enemies.empty())
    {
        return enemies.end();
    }
    auto random_enemy_index = rand() % enemies.size();
    auto it = enemies.begin();
    advance(it, random_enemy_index);
    if ((shot_chance % 100) < SHOT_PROBABILITY)
    {
        it->get_shot();
    }
    if (it->get_health_points() == 0)
    {
        return it;
    }
    return enemies.end();
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
