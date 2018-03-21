#include <ncurses.h>

int main() 
{
  initscr();
  raw();
  
  // display only test
  attron(A_STANDOUT | A_UNDERLINE);
  mvprintw(12,40,"RED THIS NOW");
  attroff(A_STANDOUT | A_UNDERLINE); 
  
  getch();
  endwin();
  
  return 0;
}
