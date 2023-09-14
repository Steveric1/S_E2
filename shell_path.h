#ifndef _SHELL_PATH_H
#define _SHELL_PATH_H

#include "main.h"
#include "strtok.h"

typedef struct directory
{
    char *path;
    struct directory *link;
}directory_n;
directory_n *add_at_beg(directory_n **headptr, const char *path);
directory_n *dir_at_the_end(directory_n **dir_head, const char *path);
void free_dir(directory_n **head_ptr);

typedef struct helper
{
    const char *path;
    char delim;
} path_helper;

directory_n *path_to_list(directory_n **tail_ptr, path_helper help);
directory_n *path_wrapper(path_helper help);

#endif /*SHELL_PATH_H*/