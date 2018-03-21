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

void make_ball(WINDOW *w, int y, int x, int lenght)
{
  //set snake coords
  std::vector<std::pair<int, int>> snake;
  for (int i = x-lenght; i <= x; ++i)
  {
    snake.push_back(std::make_pair(y,i));
  }

  int max_y = 0, max_x = 0;
  int next_x = x;
  int next_y = y;
  int direction_x = 1;
  int direction_y = 1;
  int change_direction = 0;

  getmaxyx(w, max_y, max_x);

  while (1)
  {
    wclear(w);
    box(w, '|', '-');

    //paint snake
    for (std::vector<std::pair<int,int>>::iterator it=snake.begin(); it!=snake.end(); ++it)
    {
      mvwprintw(w, it->first, it->second, "o");
    }

    usleep(DELAY);

    if (change_direction == 5)
    {
      do
      {
        direction_x = rand() % 3 - 1; 
        direction_y = rand() % 3 - 1;
      } while (direction_x == 0 && direction_y == 0);
      change_direction = 0;
    }

    //todo
    snake.erase(snake.begin()); //removes first element (snake's ass)
    next_x = x + direction_x;
    next_y = y + direction_y;  
    snake.push_back(make_pair(next_y, next_x));

    if (next_x >= max_x-1 || next_x < 1)
    {
      direction_x *= -1;
    }
    else
    {
      x += direction_x;
    }

    if (next_y >= max_y-1 || next_y < 1)
    {
      direction_y *= -1;
    }
    else
    {
      y += direction_y;
    }

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
 /* initialize random seed: */
  srand(time(NULL));

  int ax = 5, ay = 5;
  int bx = 5, by = 5;
  int cx = 5, cy = 5;
  int dx = 5, dy = 5;
  WINDOW *a, *b, *c, *d;
  char command[100];
  int maxx, maxy, halfx, halfy;
  
  initscr();
  noecho();
  curs_set(FALSE);
  refresh();
  
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_BLUE);
  init_pair(2, COLOR_BLACK, COLOR_RED);
  init_pair(3, COLOR_BLACK, COLOR_GREEN);
  init_pair(4, COLOR_BLACK, COLOR_CYAN);
  /* calculate window sizes and locations */
  getmaxyx(stdscr, maxy, maxx);
  halfx = maxx >> 1;
  halfy = maxy >> 1;
  /* create four windows to fill the screen */
  a = newwin(halfy, halfx, 0, 0);
  b = newwin(halfy, halfx, 0, halfx);
  c = newwin(halfy, halfx, halfy, 0);
  d = newwin(halfy, halfx, halfy, halfx);
  /* Write to each window */
  box(a, '|', '-');
  box(b, '|', '-');
  box(c, '|', '-');
  box(d, '|', '-');
  mvwaddstr(a, 0, 0, "");
  wrefresh(a);
  mvwaddstr(b, 0, 0, "");
  wrefresh(b);
  mvwaddstr(c, 0, 0, "");
  wrefresh(c);
  mvwaddstr(d, 0, 0, "");
  wrefresh(d);

  thread t1(make_ball, a, halfy/2, halfx/2, 5);
  thread t2(make_ball, b, halfy/2, halfx/2, 5);
  thread t3(make_ball, c, halfy/2, halfx/2, 5);
  thread t4(make_ball, d, halfy/2, halfx/2, 5);
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
