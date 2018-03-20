// Napisać program w którym wątki przyjmują kilka parametrów przy starcie
// (przykładowa sygnatura: `void foo(int a, double b)`)

#include <iostream>
#include <thread>

void foo(int a, double b)
{
  std::cout << "foo: " << a << ", " << b << std::endl;
}

void bar(float c, long d)
{
  std::cout << "bar: " << c << ", " << d << std::endl;
}

int main()
{
  std::thread fooThread(foo,1,2.3);
  std::thread barThread(bar,4.5,6);

  fooThread.join();     
  barThread.join();	

  std::cout << "main done" << std::endl;

  return 0;
}