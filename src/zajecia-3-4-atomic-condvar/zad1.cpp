/*
 * Porownac szybkosc sumowania pod std::mutex oraz za pomoca std::atomic
 * (program1-mutex-sum.cpp, oraz program2-atomic-sum.cpp).
 */

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <chrono>

//program1
long long sum1 = 0;
std::mutex mx;

//program2
std::atomic<long long> sum2(0);

void foo()
{
  for (int i = 0; i < 1000000; i++)
    {
      mx.lock();
      sum1 += 7;
      mx.unlock();
    }
}

void program1()
{
  auto start = std::chrono::steady_clock::now();
  std::vector<std::thread> threads;

  for (int i = 0; i < 10; i++)
    threads.push_back(std::thread(foo)); // startuje nowy watek i wrzca do wektora

  for (auto& thread : threads) // for (int i = 0; i < 10; i++)
    thread.join();         // threads[i].join();

  auto end = std::chrono::steady_clock::now();
  std::cout << "Program1: " << sum1 << std::endl;
  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl << std::endl;
}

void bar()
{
  for (int i = 0; i < 1000000; i++)
    sum2 += 7;
}

void program2()
{
  auto start = std::chrono::steady_clock::now();
  std::vector<std::thread> threads;

  for (int i = 0; i < 10; i++)
    threads.push_back(std::thread(bar)); // startuje nowy watek i wrzca do wektora

  for (auto& thread : threads) // for (int i = 0; i < 10; i++)
    thread.join();         // threads[i].join();

  auto end = std::chrono::steady_clock::now();
  std::cout << "Program2: " << sum2 << std::endl;
  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
}

int main()
{
  program2();
  program1();

  return 0;
}
