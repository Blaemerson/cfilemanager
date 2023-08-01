#include <dirent.h>
#include <unistd.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

typedef struct file {
    char *name;
    char type;
} file_t;

typedef struct directory {
    file_t *files;
    size_t size;
    char *path;
    void (*add)(struct directory *, file_t *file);
    void (*print)(struct directory *, WINDOW *window);
} directory_t;

void sort_files(directory_t *dir) {
    for (int i = 0; i < dir->size; i++) {
        for (int j = 0; j < dir->size - i - 1; j++) {
            if (strcmp(dir->files[j].name, dir->files[j + 1].name) > 0) {
                file_t tmp = dir->files[j];
                dir->files[j] = dir->files[j + 1];
                dir->files[j + 1] = tmp;
            }
        }
    }
}

void add(directory_t *dir, file_t *file) {
    file_t *tmp = malloc((dir->size + 1) * sizeof(file_t));
    if (tmp == NULL) {
        return;
    }

    for (int i = 0; i < dir->size; i++) {
        tmp[i] = dir->files[i];
    }

    tmp[dir->size] = *file;
    dir->size = dir->size + 1;

    free(dir->files);

    dir->files = tmp;
}

void print(directory_t *dir, WINDOW *window) {
    for (int i = 0; i < dir->size; i++) {
        mvwprintw(window, i + 1, 2, "%s", dir->files[i].name);
    }
}


static const directory_t open_dir(char *path) {
    struct dirent *dirent;
    DIR *directory = opendir(path);

    if (directory == NULL) {
        printf("Error opening dir %s", path);
        return (directory_t) {};
    }

    directory_t dir = {.size = 0, .files = NULL, .add = add, .print = print};
    while ((dirent = readdir(directory)) != NULL) {
        file_t f = {.name = dirent->d_name, .type = dirent->d_type};
        dir.add(&dir, &f);
    }

    closedir(directory);

    sort_files(&dir);

    return dir;
}

void notify(WINDOW *win, char* msg) {
    box(win, 0, 0);
    mvwprintw(win, 1, 1, "%s", msg);
    wrefresh(win);
    getch();
    wclear(win);
    wrefresh(win);
}


int main(int argc, char **argv)
{
    initscr();

    // creating a window;
    // with height = 15 and width = 10
    // also with start x axis 10 and start y axis = 20
    int stdscr_w;
    int stdscr_h;
    getmaxyx(stdscr, stdscr_h, stdscr_w);
    WINDOW *win_left = newwin(stdscr_h, stdscr_w / 2, 0, 0);
    WINDOW *win_right = newwin(stdscr_h, stdscr_w / 2, 0, stdscr_w / 2);
    WINDOW *notifier = newwin(stdscr_h / 3, stdscr_w / 6, (stdscr_h / 2) - (stdscr_h / 6), (stdscr_w / 2) - (stdscr_w / 12));
    refresh();

    // refreshing the window
    wrefresh(win_left);
    wrefresh(win_right);
    // wrefresh(notifier);

    char cwd[256];
    getcwd(cwd, sizeof(cwd));
    directory_t focused_dir = open_dir(cwd);

    WINDOW* focus = win_left;
    char c;
    do {
        focused_dir.print(&focused_dir, focus);

        switch (c) {
            case ('j'):
                notify(notifier, "not implemented yet");
                break;
            case ('k'):
                notify(notifier, "not implemented yet");
                break;
            case ('h'):
                notify(notifier, "not implemented yet");
                break;
            case ('l'):
                notify(notifier, "not implemented yet");
                break;
            case ('p'):
                focus = win_right;
                break;
        }


        // making box border with default border styles
        box(win_left, 0, 0);
        wrefresh(win_left);
        box(win_right, 0, 0);
        wrefresh(win_right);

    } while ((c = getch()) && c != 'q');

    endwin();

    free(focused_dir.files);

    return 0;
}
