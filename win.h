#pragma once

#include "dir.h"
#include <curses.h>

struct win_info {
    size_t w;
    size_t h;
};

typedef struct pane {
    WINDOW* pad;
    directory_t dir;
    size_t rowpos;
} pane_t ;

struct win_info get_win_size(WINDOW* win);
#define get_winfo get_win_size(stdscr);

WINDOW* make_win_relative(float h_ratio, float w_ratio, float y_pos_ratio, float x_pos_ratio);

WINDOW* make_win_centered(int h, int w);

void redraw(WINDOW *win);
void resize(WINDOW *win, float h_ratio, float w_ratio, float y_pos_ratio, float x_pos_ratio);

void notify(WINDOW *win, char* msg);

static void hide(WINDOW *win);
