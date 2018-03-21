#include <iostream>
#include <thread>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <vector>

using namespace std;
#define DELAY 100000
#define SNAKE_LENGHT 10

void make_ball(WINDOW *w, int y, int x)
{
  //set snake coords
  std::vector<std::pair<int, int>> snake;
  for (int i = x-SNAKE_LENGHT; i <= x; ++i)
  {
    snake.push_back(std::make_pair(y,i));
  }

  int max_y = 0, max_x = 0;
  int next_x = x;
  int next_y = y;
  int direction_x = 1;
  int direction_y = 0;
  int change_direction = 0;

  getmaxyx(w, max_y, max_x);

  while (1)
  {
    wclear(w);
    box(w,0,0);

    //paint snake
    for (std::vector<std::pair<int,int>>::iterator it=snake.begin(); it!=snake.end(); ++it)
    {
      mvwprintw(w, it->first, it->second, "O");
    }

    //choose random direction after 5 steps
    if (change_direction == 5)
    {
      do
      {
        direction_x = rand() % 3 - 1; 
        direction_y = rand() % 3 - 1;
      } while ((direction_x == 0 && direction_y == 0));
      change_direction = 0;
    }

    usleep(DELAY);

    next_x = x + direction_x;
    next_y = y + direction_y;  

    //pls stay in the box
    //corners
    if ((next_x >= max_x-2 || next_x < 2) && (next_y >= max_y-2 || next_y < 2))
    {
      direction_x *= -1;
      direction_y *= -1;
    }
    //borders
    else 
    {
      if (next_x >= max_x-1 || next_x < 1)
      {
        direction_x = 0;
        direction_y = rand() % 2 == 0 ? -1 : 1;
      }
      if (next_y >= max_y-1 || next_y < 1)
      {
        direction_y = 0;
        direction_x = rand() % 2 == 0 ? -1 : 1;
      }
    }

    x += direction_x;
    y += direction_y;

    //increment snake
    snake.erase(snake.begin()); //removes first element (snake's ass)
    snake.push_back(make_pair(y, x));

    change_direction++;
  }
}

void refresh_windows(WINDOW *a, WINDOW *b, WINDOW *c, WINDOW *d)
{
  while(1) {
    wrefresh(a);
    wrefresh(b);
    wrefresh(c);
    wrefresh(d);
    usleep(DELAY);
  }
}

int main(int argc, char *argv[])
{
 /* initialize random seed */
  srand(time(NULL));
  
  initscr();
  noecho();
  curs_set(FALSE);
  refresh();
  
  /* calculate window sizes and locations */
  int maxx, maxy, halfx, halfy;
  getmaxyx(stdscr, maxy, maxx);
  halfx = maxx >> 1;
  halfy = maxy >> 1;
  
  /* create four windows to fill the screen */
  WINDOW *a, *b, *c, *d;
  a = newwin(halfy, halfx, 0, 0);
  b = newwin(halfy, halfx, 0, halfx);
  c = newwin(halfy, halfx, halfy, 0);
  d = newwin(halfy, halfx, halfy, halfx);
  
  thread t1(make_ball, a, halfy/2, halfx/2);
  thread t2(make_ball, b, halfy/2, halfx/2);
  thread t3(make_ball, c, halfy/2, halfx/2);
  thread t4(make_ball, d, halfy/2, halfx/2);
  thread t5(refresh_windows, a, b, c, d);

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();

  getch();
  endwin();
  
  return 0;
}
