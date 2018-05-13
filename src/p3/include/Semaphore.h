//
// Created by Hanna Grodzicka on 02.05.2018.
//

#ifndef ARCHERS_SEMAPHORE_H
#define ARCHERS_SEMAPHORE_H

#include <mutex>
#include <condition_variable>

class Semaphore
{
public:
    Semaphore() = delete;

    Semaphore(const Semaphore &) = delete;

    static void notify();

    static void wait();

    static void lock();

    static void unlock();

private:
    static std::condition_variable cv;
    static std::mutex mx;
    static int counter;
};


#endif //ARCHERS_SEMAPHORE_H
