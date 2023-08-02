#include <stdlib.h>
#include <unistd.h>

#include "win.h"
#include "dir.h"

int main(int argc, char **argv)
{
    initscr();
    noecho();

    WINDOW *notifier  = make_win_centered(4, 24);
    WINDOW *win_left  = make_win(1, 0.5f, 0, 0);
    WINDOW *win_right = make_win(1, 0.5f, 0, 0.5f);

    // refreshing the window
    refresh();

    redraw(win_left);
    redraw(win_right);

    char cwd[256];
    getcwd(cwd, sizeof(cwd));
    directory_t focused_dir = open_dir(cwd);

    WINDOW* focus = win_left;

    char c;
    do {
        focused_dir.print(&focused_dir, focus);

        switch (c) {
            case ('j'):
                notify(notifier, "Not implemented yet");
                break;
            case ('k'):
                notify(notifier, "Not implemented yet");
                break;
            case ('h'):
                notify(notifier, "Not implemented yet");
                break;
            case ('l'):
                notify(notifier, "Not implemented yet");
                break;
            case ('d'):
                notify(notifier, "Not implemented yet");
                break;
            case ('c'):
                notify(notifier, "Not implemented yet");
                break;
            case (' '):
                notify(notifier, "Not implemented yet");
                break;
            case ('p'):
                focus = win_right;
                break;
            default:
                break;
        }

        redraw(win_left);
        redraw(win_right);

    } while ((c = getch()) && c != 'q');

    endwin();

    free(focused_dir.files);

    return 0;
}
