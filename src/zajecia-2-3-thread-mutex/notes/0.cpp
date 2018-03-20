#include <mutex>

std::mutex mx;
std::lock_guard<std::mutex> mx(?);  //wrapper na mutex; destruktor przy końcu scope'a

void foo()
{
	mx.lock();
  //...
  mx.unlock();  //bez unlocka = zakleszczenie; ciężkie do debuggowania
}

void bar()
{
  mx.lock();
  //...
  mx.unlock();
}