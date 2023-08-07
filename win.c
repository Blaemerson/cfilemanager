#include <curses.h>
#include "win.h"

struct win_info get_win_size(WINDOW* win) {
    int stdscr_w;
    int stdscr_h;
    getmaxyx(win, stdscr_h, stdscr_w);

    return (struct win_info){.w = stdscr_w, .h = stdscr_h};
}

WINDOW* make_win_relative(float h_ratio, float w_ratio, float y_pos_ratio,float x_pos_ratio) {
    struct win_info winfo = get_winfo

    return newwin(winfo.h * h_ratio, winfo.w * w_ratio, winfo.h * y_pos_ratio, winfo.w * x_pos_ratio);
}

WINDOW* make_win_centered(int h, int w) {
    struct win_info winfo = get_winfo

    return newwin(h, w, (winfo.h / 2) - (h / 2), (winfo.w / 2) - (w / 2));
}

void redraw(WINDOW *win) {
    box(win, 0, 0);
    wrefresh(win);
}

void resize(WINDOW *win, float h_ratio, float w_ratio, float y_pos_ratio, float x_pos_ratio) {
    struct win_info winfo = get_winfo;

    wresize(win, winfo.h * h_ratio, winfo.w * w_ratio);
    mvwin(win, winfo.h * y_pos_ratio, winfo.w * x_pos_ratio);
}

void hide(WINDOW *win) {
    wclear(win);
    wrefresh(win);
}

void notify(WINDOW *win, char* msg) {
    box(win, 0, 0);
    mvwprintw(win, 1, 1, "%s", msg);
    mvwprintw(win, 2, 1, "Press any key...");
    wrefresh(win);
    getch();
    hide(win);
}
