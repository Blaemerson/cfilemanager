#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "win.h"
#include "dir.h"

int main(int argc, char **argv) {
    initscr();
    noecho();
    refresh();

    WINDOW *win_notify = make_win_centered(6, 24);
    WINDOW *win_left   = make_win_relative(1.0f, 0.5f, 0.0f, 0.0f);
    WINDOW *win_right  = make_win_relative(1.0f, 0.5f, 0.0f, 0.5f);

    redraw(win_left);
    redraw(win_right);

    char cwd[256];
    getcwd(cwd, sizeof(cwd));
    directory_t focused_dir = open_dir(cwd);

    WINDOW* focus = win_left;

    char c;
    do {
        wclear(win_left);
        wclear(win_right);

        focused_dir.print(&focused_dir, focus);

        switch (c) {
            case ('j'):
                notify(win_notify, "Not implemented yet");
                break;
            case ('k'):
                notify(win_notify, "Not implemented yet");
                break;
            case ('h'):
                notify(win_notify, "Not implemented yet");
                break;
            case ('l'):
                notify(win_notify, "Not implemented yet");
                break;
            case ('d'):
                notify(win_notify, "Not implemented yet");
                break;
            case ('c'):
                notify(win_notify, "Not implemented yet");
                break;
            case (' '):
                notify(win_notify, "Not implemented yet");
                break;
            case ('p'):
                focus = win_right;
                break;
            default:
                break;
        }

        redraw(win_left);
        redraw(win_right);

        refresh();

    } while ((c = getch()) && c != 'q');

    endwin();

    free(focused_dir.files);

    return 0;
}
