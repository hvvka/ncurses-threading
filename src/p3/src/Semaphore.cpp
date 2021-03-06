//
// Created by Hanna Grodzicka on 02.05.2018.
//

#include "Semaphore.h"

std::mutex Semaphore::mx;
std::condition_variable Semaphore::cv;
std::atomic<int> Semaphore::counter;

void Semaphore::notify()
{
    ++counter;
    cv.notify_all();
}

void Semaphore::wait()
{
    std::unique_lock<std::mutex> lock(mx);
    cv.wait(lock, [] { return counter != 0; });
    --counter;
}

void Semaphore::lock()
{
    mx.lock();
}

void Semaphore::unlock()
{
    mx.unlock();
}

std::condition_variable &Semaphore::get_condition_variable()
{
    return cv;
}

std::mutex &Semaphore::get_mutex()
{
    return mx;
}
