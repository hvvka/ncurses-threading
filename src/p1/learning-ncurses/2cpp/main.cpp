#include <ncurses.h>

using namespace std;

int main(int argc, char** argv)
{
  initscr();

  int x, y;
  x = y = 10;
  // moves the cursor to the specified location
  move(y, x);
  printw("Hello move!");

  refresh();

  int c = getch();
  // clears the screen
  clear();

  mvprintw(0, 0,"%d", c);
  refresh();
  

  getch();
  endwin();

  return 0;
}
