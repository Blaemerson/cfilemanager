#include <curses.h>
#include "win.h"

WINDOW* make_win(float h_ratio, float w_ratio, float y_pos_percent,float x_pos_percent) {
    int stdscr_w;
    int stdscr_h;
    getmaxyx(stdscr, stdscr_h, stdscr_w);

    return newwin(stdscr_h * h_ratio, stdscr_w * w_ratio, stdscr_h * y_pos_percent, stdscr_w * x_pos_percent);
}

WINDOW* make_win_centered(int h, int w) {
    int stdscr_w;
    int stdscr_h;
    getmaxyx(stdscr, stdscr_h, stdscr_w);

    return newwin(h, w, (stdscr_h / 2) - (h / 2), (stdscr_w / 2) - (w / 2));
}

void redraw(WINDOW *win) {
    box(win, 0, 0);
    wrefresh(win);
}

void notify(WINDOW *win, char* msg) {
    box(win, 0, 0);
    mvwprintw(win, 1, 1, "%s", msg);
    mvwprintw(win, 2, 1, "Press any key...");
    wrefresh(win);
    getch();
    wclear(win);
    wrefresh(win);
}
