/*
 * Przerobic program z zadania 4 z poprzednich zajec, 
 * tak aby uzywal zmiennych warunkowych
 * zamiast aktywnego czekania na rozmiarze wektora.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>

std::mutex mx;
std::vector<std::string> words;
std::condition_variable cv;

void read(std::string filename)
{
  std::ifstream file(filename);
  if (file.is_open())
  {
    std::string word;
    while (file >> word)
    {
      {
        std::unique_lock<std::mutex> lock(mx);
        words.push_back(word);
      }
      cv.notify_one();
    }
  }
  else std::cout << "Plik nie został otwarty." << std::endl;

  file.close();
}

void has_words()
{
  std::unique_lock<std::mutex> lock(mx);
  while (true)
  {
    cv.wait(lock, []{ return words.size() > 0; });
    auto word = words.back();
    std::cout << word << ": " << word.length() << std::endl;
    words.pop_back();
  }
}

int main()
{
	std::string filename = "test.txt";

  std::thread t1(read, filename);
  std::thread t2(has_words);
  std::thread t3(has_words);

  t1.join();
  t2.join();
  t3.join();
    
	return 0;
}