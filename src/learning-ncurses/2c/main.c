#include <ncurses.h>

int main() 
{
  initscr();
  raw();
  int derp = 4;
  printw("This is bog standard output %d", derp);
  addch('a');

  move(12,13);
  mvprintw(15,20,"Movement");
  mvaddch(12,50,'@');

  getch();
  endwin(); //freeze the memory on the screen

  return 0;
}
