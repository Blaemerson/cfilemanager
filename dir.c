#include "dir.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

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


const directory_t open_dir(char *path) {
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
