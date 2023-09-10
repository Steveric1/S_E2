#include "main.h"

/**
 * str_concat - concatenate into strings together
 * @len: length
 * @delim: delimeter
 * @prev: previous string
 * @next: next string
 * 
 * Return: a pointer to the calling function
*/
char *str_concat(size_t *len, const char *delim, const char *prev, const char *next)
{
    char *destination = NULL;
    size_t prev_len, next_len, delim_len;
    prev_len = _strlen(prev ? prev : "");
    delim_len = _strlen(delim ? delim : "");
    next_len = _strlen(next ? next : "");

    destination = malloc(1 * (prev_len + delim_len + next_len + 1));
    if (destination != NULL)
    {
        _strcpy(destination, prev ? prev : "");
        _strcpy(destination + prev_len, delim ? delim : "");
        _strcpy(destination + prev_len + delim_len, next ? next : "");
        if (len)
            *len = (prev_len + delim_len + next_len + 1);
    }
    return (destination);
}