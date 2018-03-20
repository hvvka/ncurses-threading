// Napisać program w którym jeden z wątków 
// czyta słowa z dużego pliku i dorzuca do współdzielonego wektora. 
// Dwa inne wątki powinny w nieskończoność sprawdzać 
// czy wektor posiada jakieś słowa i jeśli tak,
// to pobierać jedno słowo i wyświetlać na ekran jego długość. 
// Dostęp do wektora powinien odbywać się bezpiecznie wielowątkowo

#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>

std::mutex mx;
std::vector<std::string> words;

void read(std::string filename)
{
  std::ifstream file("test.txt");
  if(file.is_open())
  {
    std::string word;
    while(file >> word)
    {
      mx.lock();
      words.push_back(word);
      mx.unlock();
    }
  }
  else std::cout << "Plik nie został otwarty." << std::endl;

  file.close();
}

void has_words()
{
  while(true)
  {
    mx.lock();
    if(words.size() > 0) //!words.empty()
    {
      auto word = words.back();
      std::cout << word << ": " << word.length() << std::endl;
      words.pop_back();
    }
    mx.unlock();
  }
}

int main()
{
  std::string line;
	std::string filename;

  std::thread t1(read, filename);
  std::thread t2(has_words);
  std::thread t3(has_words);

  t1.join();
  t2.join();
  t3.join();
    
	return 0;
}