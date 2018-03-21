#include <ncurses.h>

using namespace std;

int main(int argc, char** argv)
{
  // initializes the screen
  // sets up memory and clears the screen
  initscr();
  
  // prints a string(consta char *) to a window
  printw("Hello ncurses!");
  
  // refreshes the screen to mach whats in memory
  refresh();

  // what for user input, returns int value of that key
  int c = getch();
  printw("%d", c);

  getch();

  endwin();
  // dealloocates memory and ends ncurses

  return 0;
}
