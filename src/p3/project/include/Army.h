//
// Created by Hanna Grodzicka on 02.05.2018.
//

#ifndef ARCHERS_ARMY_H
#define ARCHERS_ARMY_H

#include <atomic>
#include "Archer.h"

class Army
{
private:
    army_type army_color;
    std::list<Archer> army;
    std::atomic<int> score;

public:
    explicit Army(army_type army_color);
    virtual ~Army() = default;
    std::list<Archer> get_army();
    int get_score();
    army_type get_color();
};


#endif //ARCHERS_ARMY_H
