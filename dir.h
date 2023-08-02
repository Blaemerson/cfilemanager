#include <curses.h>
#include <stddef.h>

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

void sort_files(directory_t *dir);

void add(directory_t *dir, file_t *file);

void print(directory_t *dir, WINDOW *window);

const directory_t open_dir(char *path);
