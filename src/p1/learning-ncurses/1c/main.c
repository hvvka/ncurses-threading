#include <ncurses.h>

int main() 
{
  initscr(); // creates stdscr
  raw(); // cbreak();
  printw("Hello world");
  getch();
  endwin(); //freeze the memory on the screen

  return 0;
}
