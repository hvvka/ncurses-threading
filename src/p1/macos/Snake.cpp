#include <iostream>
#include <thread>
#include <mutex>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <vector>

#define DELAY 60000
#define SNAKE_LENGHT 10

std::mutex mx;

void make_ball(WINDOW *w, int y, int x)
{
  //set snake coords
  std::vector<std::pair<int, int>> snake;
  for (int i = x-SNAKE_LENGHT-1; i <= x; ++i)
  {
    snake.push_back(std::make_pair(y,i));
  }
  std::vector<std::pair<int, int>> prev_snake(snake);

  int max_y = 0, max_x = 0;
  int next_x = x;
  int next_y = y;
  int direction_x = 1;
  int direction_y = 0;
  int change_direction = 0;

  getmaxyx(w, max_y, max_x);

  while (1)
  {
    // wclear(w);
    // box(w,0,0);

   {
      // clear snake
      std::lock_guard<std::mutex> mx_lock(mx);
      for (std::vector<std::pair<int,int>>::iterator it=prev_snake.begin(); it!=prev_snake.end(); ++it)
      {
        mvwprintw(w, it->first, it->second, " ");
      }
      //paint snake
      for (std::vector<std::pair<int,int>>::iterator it=snake.begin(); it!=snake.end(); ++it)
      {
        mvwprintw(w, it->first, it->second, "O");
      }
    }
    usleep(DELAY);

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

    //for clearing snake
    prev_snake = snake;
    //increment snake
    snake.erase(snake.begin()); //removes first element (snake's ass)
    snake.push_back(std::make_pair(y, x));

    change_direction++;
  }
}

void refresh_windows(WINDOW *a, WINDOW *b, WINDOW *c, WINDOW *d)
{
  while(1) {
    {
      std::lock_guard<std::mutex> mx_lock(mx);
      wrefresh(a);
      wrefresh(b);
      wrefresh(c);
      wrefresh(d);
    }
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

  /* colors */
  start_color();
  init_color(COLOR_RED, 300, 100, 150);
  init_color(COLOR_CYAN, 40, 200, 300);
  init_color(COLOR_YELLOW, 300, 330, 70);
  init_color(COLOR_MAGENTA, 80, 300, 200);
  init_pair(1,COLOR_WHITE, COLOR_RED);
  init_pair(2,COLOR_WHITE, COLOR_CYAN);
  init_pair(3,COLOR_WHITE, COLOR_YELLOW);
  init_pair(4,COLOR_WHITE, COLOR_MAGENTA);
  wbkgd(a, COLOR_PAIR(1));
  wbkgd(b, COLOR_PAIR(2));
  wbkgd(c, COLOR_PAIR(3));
  wbkgd(d, COLOR_PAIR(4));
  box(a,0,0);
  box(b,0,0);
  box(c,0,0);
  box(d,0,0);
  
  std::thread t1(make_ball, a, halfy/2, halfx/2);
  std::thread t2(make_ball, b, halfy/2, halfx/2);
  std::thread t3(make_ball, c, halfy/2, halfx/2);
  std::thread t4(make_ball, d, halfy/2, halfx/2);
  std::thread t5(refresh_windows, a, b, c, d);

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();

  getch();
  endwin();
  
  return 0;
}
