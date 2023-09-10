#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <syslog.h>
#include <unistd.h>
#include <stdbool.h>

/**STRING PRTOTYPES**/
char *_strcat(char *dest, const char *src);
ssize_t _memchr(const void *s, int c, size_t n);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
bool _isspace(int c);
char *_strdup(char *str);
char *_strstr(const char *haystack, const char *needle);
void *_memcpy(void *dest, const void *src, size_t n);
void *_realloc(void *buffer, size_t old_size, size_t new_size);
size_t _strlen(const char *s);
char *_strcpy(char *dest, const char *src);

/**SHELL ERROR**/
void printerror(char **av, int count, char **arg);
int write_error_stderr(int error);

/**SHELL HELPER**/
void free_all(const unsigned int n, ...);
store_info_t *init_prmpt(char **av, int ac);
bool read_usr_input(store_info_t *input_info);

/**
 * store_info - store shell information
 * @argv: argument
 * @argc: argument counter
 * @interactive: shell interactive
 * @fileno: fileno
 * @file: file
 * @error: error
 * @status: status
*/
typedef struct store_info
{
    char **argv;
    int argc;
    int interactive;
    int fileno;
    char *file;
    size_t line_read;
    char *line;
    int error;
    int status;
}store_info_t;

/**QUOTE STRING PROCESS**/

/**
 * enum quote - Represents quoting states for text processing.
 * @QUOTE_NONE: No quoting state.
 * @QUOTE_DOUBLE: Inside a double-quoted section.
 * @QUOTE_SINGLE: Inside a single-quoted section.
 * @QUOTE_ESCAPE: Following an escape character.
*/
typedef enum quote
{
    QUOTE_NONE   = 0x0,
    QUOTE_WORD   = 0x1,
    QUOTE_DOUBLE = 0x2,
    QUOTE_SINGLE = 0x4,
    QUOTE_ESCAPE = 0x8
}quote_state;

typedef size_t (*quote_state_fp)(const char *, quote_state *);
quote_state_fp quote_factory(quote_state str);
quote_state quote_proc(char c);

size_t quote_double(const char *str, quote_state *state);
size_t quote_single(const char *str, quote_state *state);
size_t quote_escape(const char *str, quote_state *state);
size_t quote_none(const char *str, quote_state *state);
size_t quote_word(const char *str, quote_state *state);
size_t quote_str_len(const char *str, quote_state state);

/******STRING*******/
char *str_concat(size_t *len, const char *delim, const char *prev, const char *next);
#endif /*MAIN_H*/