//
// Created by Hanna Grodzicka on 02.05.2018.
//

#include <Application.h>

int main(int argc, char *argv[])
{
//    new Application();

//    auto * enemy = new Army(RED);
//    auto archers = enemy->get_archers();
//    for(int i = 0; i < 24; ++i) {
//        std::cout << "x=" << archers.front().get_position().second << "; ";
//        std::cout << "y=" << archers.front().get_position().first << std::endl;
//        archers.pop_front();
//    }

    Army army(BLUE);
    std::cout << army.get_archers().size() << std::endl;
    std::cout << army.get_archers().front().get_health_points() << std::endl;
    army.get_archers().front().shot_enemy(army.get_archers());
    std::cout << army.get_archers().front().get_health_points() << std::endl;
    army.get_archers().front().shot_enemy(army.get_archers());
    std::cout << army.get_archers().front().get_health_points() << std::endl;
    army.get_archers().front().shot_enemy(army.get_archers());
    std::cout << army.get_archers().front().get_health_points() << std::endl;

    return 0;
}