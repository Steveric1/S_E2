#include "main.h"
#include "getline.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    char *line;
    while ((line = my_getline(fd)) != NULL)
    {
        printf("%s", line); // Print each line
        free(line);         // Don't forget to free the memory allocated by my_getline
    }

    close(fd); // Close the file descriptor when done

    return 0;
}