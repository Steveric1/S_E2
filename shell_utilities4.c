#include "main.h"

/**
 * quote_factory - function pointer string processor helper
 * @state: state
 * 
 * Return: state with associated c
*/
quote_state_fp quote_factory(quote_state state)
{
    switch (state)
    {
        case QUOTE_NONE:
           return (quote_none);
        case QUOTE_DOUBLE:
           return (quote_double);
        case QUOTE_SINGLE:
           return (quote_single);
        case QUOTE_ESCAPE:
           return (quote_escape);
        case QUOTE_WORD:
           return (quote_word);
    }
    return (NULL);
}

/**
 * quote_str_len - get the length of state
 * @str: string
 * @state: state
 * 
 * Return: length
*/
size_t quote_str_len(const char *str, quote_state state)
{
   return (quote_factory(state)(str, NULL));
}

/**
 * process_usr_input - Process user input
 * @line_input: line input parameter
 * @fd: file descriptor
 * Return: state
*/
quote_state process_usr_input(char **line_input, int fd)
{
    char *line = my_getline(fd), *line_input = line;
    static quote_state state = QUOTE_NONE; /*maintain state accross function calls*/
    size_t index = 0;

    while (line)
    {
        switch (state & (QUOTE_DOUBLE | QUOTE_SINGLE))
        {
            case QUOTE_DOUBLE:
            case QUOTE_SINGLE:
                do
                {
                    index += quote_str_len(line + index, state);
                    if (line[index] == '\0')
                       continue;
                    if (state & (QUOTE_DOUBLE | QUOTE_SINGLE))
                       index += 1;
                    /*Fall-through*/
            default:
		            state = quote_factory(line[index]);
		            if (state & (QUOTE_DOUBLE | QUOTE_SINGLE | QUOTE_ESCAPE))
			            index += 1;
                } while (line[index]);
        }
    }
    return (state);
}
