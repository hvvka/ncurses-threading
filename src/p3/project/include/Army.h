//
// Created by Hanna Grodzicka on 02.05.2018.
//

#ifndef ARCHERS_ARMY_H
#define ARCHERS_ARMY_H

#include <atomic>
#include <vector>
#include "Archer.h"

class Army
{
private:
    army_type army_color;
    std::vector <Archer> army;
    std::atomic<int> score;

public:
    explicit Army(army_type army_color);

    virtual ~Army() = default;

    std::vector <Archer> &get_archers();

    int get_score();

    army_type get_color();
};


#endif //ARCHERS_ARMY_H
