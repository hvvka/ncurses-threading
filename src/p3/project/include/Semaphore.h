//
// Created by Hanna Grodzicka on 02.05.2018.
//

#ifndef ARCHERS_SEMAPHORE_H
#define ARCHERS_SEMAPHORE_H

#include <mutex>
#include <condition_variable>

class Semaphore
{
private:
    Semaphore();
    Semaphore( const Semaphore & );
    static std::mutex mx;
    static std::condition_variable cv;
    static int counter;

public:
    static void notify();
    static void wait();
    static void lock();
    static void unlock();
};


#endif //ARCHERS_SEMAPHORE_H
