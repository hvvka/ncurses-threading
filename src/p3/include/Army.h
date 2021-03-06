//
// Created by Hanna Grodzicka on 02.05.2018.
//

#ifndef ARCHERS_ARMY_H
#define ARCHERS_ARMY_H

#include "Archer.h"

#include <atomic>
#include <vector>

class Army
{
public:
    explicit Army(army_type army_color);

    Army(const Army &army);

    virtual ~Army() = default;

    std::vector<Archer> &get_archers();

    int get_score();

    army_type get_color();

    void increase_score();

    void kill_archer(std::vector<Archer>::iterator &archer);

private:
    army_type army_color;
    std::vector<Archer> army;
    std::atomic<int> score{};
};


#endif //ARCHERS_ARMY_H
