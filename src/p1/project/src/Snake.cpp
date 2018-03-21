#include <iostream>
#include <thread>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;
#define DELAY 60000

void make_ball(WINDOW *w, int x, int y)
{
  int max_y = 0, max_x = 0;
  int next_x = 0;
  int next_y = 0;
  int direction_x = 1;
  int direction_y = 1;
  int change_direction = 0;
  getmaxyx(w, max_y, max_x);

  while (1)
  {
    wclear(w);
    box(w, '|', '-');
    mvwprintw(w, y, x, "o");

    usleep(DELAY);
    
    next_x = x + direction_x;
    next_y = y + direction_y;  

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

  thread t1(make_ball, a, 0, 0);
  thread t2(make_ball, b, 0, 0);
  thread t3(make_ball, c, 0, 0);
  thread t4(make_ball, d, 0, 0);
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
