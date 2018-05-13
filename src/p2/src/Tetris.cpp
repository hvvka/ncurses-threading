//
// Created by Hanna Grodzicka on 15.04.2018.
//

#include "Block.h"
#include <iostream>
#include <thread>
#include <ncurses.h>
#include <unistd.h>
#include <ctime>
#include <mutex>
#include <condition_variable>
#include <cstdlib>
#include <list>

#define DELAY 100000
#define TETRIS_Y(max_y) (rand() % ((max_y) - 3) + 3)
#define TETRIS_X(max_x) (rand() % ((max_x) - 3) + 3)
#define TETRIS_TYPE static_cast<block_type>(rand() % 4 + 1)

using namespace std;

std::mutex mx;
std::condition_variable cv;
std::list<block> blocks;
bool running;

void create_blocks(WINDOW *w)
{
    std::pair<int, int> current = make_pair(1, 5);  // y, x
    std::pair<int, int> prev = make_pair(current.first, current.second);
    std::pair<int, int> max = make_pair(0, 0);
    int next_y = 0;
    int direction = 1;

    getmaxyx(w, max.first, max.second);
    max.first -= 3;
    max.second -= 3;
    block tetris_block{};
    tetris_block.type = TETRIS_TYPE;

    while (running)
    {
        mx.lock();
        clean(w, tetris_block.type, prev.first, prev.second);
        paint(w, tetris_block.type, current.first, current.second);
        mx.unlock();

        prev = current;
        next_y = current.first + direction;
        usleep(DELAY);

        if (next_y >= max.first || next_y < 1)
        {
            mx.lock();
            current.second = rand() % max.second + 1;
            current.first = 1;
            clean(w, tetris_block.type, prev.first, prev.second);
            tetris_block.y = TETRIS_Y(max.first);
            tetris_block.x = TETRIS_X(max.second);
            blocks.push_front(tetris_block);
            mx.unlock();
            cv.notify_one();
            tetris_block.type = TETRIS_TYPE;
        } else
        {
            current.first += direction;
        }
    }
}

void get_block(WINDOW *w)
{
    std::unique_lock<std::mutex> lock(mx);
    while (running)
    {
        cv.wait(lock, [] { return !blocks.empty(); });
        block tetris_block = blocks.front();
        paint(w, tetris_block.type, tetris_block.y, tetris_block.x);
        blocks.pop_front();
    }
}

void refresh_windows(WINDOW *a, WINDOW *b, WINDOW *c, WINDOW *d)
{
    while (running)
    {
        mx.lock();
        wrefresh(a);
        wrefresh(b);
        wrefresh(c);
        wrefresh(d);
        mx.unlock();
        usleep(DELAY);
    }
}

int main(int argc, char *argv[])
{
    srand(static_cast<unsigned int>(time(nullptr)));

    initscr();
    noecho();
    curs_set(FALSE);
    refresh();

    /* calculate window sizes and locations */
    WINDOW *a, *b, *c, *d;
    int maxx, maxy, halfx, halfy;
    getmaxyx(stdscr, maxy, maxx);
    halfx = maxx >> 1;
    halfy = maxy >> 1;

    /* create four windows to fill the screen */
    a = newwin(halfy, halfx, 0, 0);
    b = newwin(halfy, halfx, 0, halfx);
    c = newwin(halfy, halfx, halfy, 0);
    d = newwin(halfy, halfx, halfy, halfx);

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_CYAN);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_BLUE);
    init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(6, COLOR_BLACK, COLOR_YELLOW);
    init_pair(7, COLOR_BLACK, COLOR_GREEN);
    init_pair(8, COLOR_BLACK, COLOR_RED);
    wbkgd(a, COLOR_PAIR(1));
    wbkgd(b, COLOR_PAIR(2));
    wbkgd(c, COLOR_PAIR(3));
    wbkgd(d, COLOR_PAIR(4));
    box(a, 0, 0);
    box(b, 0, 0);
    box(c, 0, 0);
    box(d, 0, 0);

    running = true;
    thread t1(create_blocks, a);
    thread t2(get_block, b);
    thread t3(get_block, c);
    thread t4(get_block, d);
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
