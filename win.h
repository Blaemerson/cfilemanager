
#include <curses.h>

WINDOW* make_win(float h_ratio, float w_ratio, float y_pos_percent,float x_pos_percent);

WINDOW* make_win_centered(int h, int w);

void redraw(WINDOW *win);

void notify(WINDOW *win, char* msg);
