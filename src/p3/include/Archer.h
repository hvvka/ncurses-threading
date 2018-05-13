//
// Created by Hanna Grodzicka on 02.05.2018.
//

#ifndef ARCHERS_ARCHER_H
#define ARCHERS_ARCHER_H

#include "ArmyType.h"

#include <vector>
#include <utility>

class Archer
{
public:
    Archer(std::pair<int, int> position, army_type army_color);

    int get_health_points();

    std::pair<int, int> get_position();

    army_type get_army_color();

    bool get_shot();

    void shot_enemy(std::vector<Archer> &enemies);

private:
    int health_points;
    std::pair<int, int> position;  // y, x
    army_type army_color;
};


#endif //ARCHERS_ARCHER_H
