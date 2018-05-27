//
// Created by Hanna Grodzicka on 02.05.2018.
//

#ifndef ARCHERS_SEMAPHORE_H
#define ARCHERS_SEMAPHORE_H

#include <mutex>
#include <condition_variable>
#include <atomic>

class Semaphore
{
public:
    Semaphore() = delete;

    Semaphore(const Semaphore &) = delete;

    static void notify();

    static void wait();

    static void lock();

    static void unlock();

    static std::mutex &get_mutex();

    static std::condition_variable &get_condition_variable();

private:
    static std::mutex mx;
    static std::condition_variable cv;
    static std::atomic<int> counter;
};


#endif //ARCHERS_SEMAPHORE_H
