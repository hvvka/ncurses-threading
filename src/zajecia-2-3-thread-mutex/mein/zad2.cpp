// Zmodyfikować `program4.cpp` tak, aby każdy wątek 
// używał lokalnego akumulatora

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

long long sum = 0;
std::mutex mx;

void foo()
{
  long long loc_sum = 0;
  for (int i = 0; i < 1000000; i++)
  {
    loc_sum += 7;
  }
  mx.lock();
  sum += loc_sum;
  mx.unlock();
}

int main()
{
  std::vector<std::thread> threads;

  for (int i = 0; i < 10; i++)
    threads.push_back(std::thread(foo));

  for (auto& thread : threads)
    thread.join();
  
  std::cout << sum << std::endl;

  return 0;
}
