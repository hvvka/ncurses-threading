#include <ncurses.h>

int main() 
{
  initscr();
  raw();
  
  start_color(); 			//starts colour
  // foreground, background
  init_pair(1,COLOR_RED,COLOR_BLUE);	//a pair of colours that corresponds together
  attron(COLOR_PAIR(1));
  printw("AHH my eyese");
  attroff(COLOR_PAIR(1));
  
  getch();
  endwin();
  
  return 0;
}
