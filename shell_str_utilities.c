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

/**
 * _strchr - locates a character in a string
 * @s: string to be searched
 * @c: character to be located
 * Return: pointer to the first occurrence of the character c in the string s
*/
ssize_t _strchr(const char *s, int c)
{
    ssize_t i;
    if (s == NULL)
       return (-1);
    for (i = 0; s[i] != '\0'; ++i)
    {
        if (s[i] == c)
            return (i);
    }
    return (-1);
}

/**
 * find_char_in_str - function to find character in a string
 * @ch: character to search
 * @size: size of the string to search
 * 
 * Return -1 if failed
*/
ssize_t find_char_in_str(const char *str, char ch, size_t size)
{
    size_t iterator;
    
    if (str == NULL)
       return (-1);
    for (iterator = 0; iterator < size; iterator ++)
    {
        if (str[iterator] == ch)
            return (iterator);
    }
    return (-1);
}

/**
 * cmd_to_split - Split a command string into tokens,
 *  considering quoting and escape characters.
 * @cmd: The input command string to be split.
 *
 * Return: The number of tokens found in the command string.
 */
size_t cmd_to_split(char *cmd)
{
    if (!cmd)
        return (0);
    cmd_t split;
    split.cmd_count = 1;

    do
    {
        while (*cmd && (split.state = quote_proc(*cmd)) != QUOTE_NONE)
        {
            if (split.state & QUOTE_WORD)
            {
                split.quote_len = quote_word(cmd, NULL);
                split.delim_indx = find_char_in_str(cmd, ';', split.quote_len);
                if (split.delim_indx != -1)
                {
                    split.quote_len = split.delim_indx;
                    *(cmd++ + split.quote_len) = '\0';
                    ++split.cmd_count;
                }
                cmd += split.quote_len;
            }
            else if (split.state & QUOTE_ESCAPE)
            {
                if (*(cmd + 1) == '\n')
                   _strcpy(cmd, cmd + 2);
                else if (*(++cmd) != '\0')
                    ++cmd;
            }
            else
            {
                cmd += quote_str_len(cmd + 1, split.state) + 1;
                if (*cmd && (split.state & (QUOTE_DOUBLE | QUOTE_SINGLE)))
                    ++cmd;
            }
        }
    } while (*(cmd += quote_str_len(cmd, QUOTE_NONE)));
    
    return (split.cmd_count);
}