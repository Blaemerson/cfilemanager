#include <dirent.h>
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
    refresh();

    // making box border with default border styles
    box(win_left, 0, 0);
    box(win_right, 0, 0);

    // move and print in window
    mvwprintw(win_left, stdscr_h / 2, stdscr_w / 4, "win_left");
    mvwprintw(win_right, stdscr_h / 2, stdscr_w / 4, "win_right");

    // refreshing the window
    wrefresh(win_left);
    wrefresh(win_right);

    directory_t cwd = open_dir("/home/blake/");

    WINDOW* focus = win_left;
    while(getch() != 'q') {
        cwd.print(&cwd, focus);

        wrefresh(win_left);
        wrefresh(win_right);

        focus = win_right;
    };

    endwin();

    free(cwd.files);

    return 0;
}
