#include "main.h"

/**
 * printerror - prints error message
 * @av: name of the program
 * @count: number of commands entered
 * @arg: command entered
 * Return: void
*/

void printerror(char **av, int count, char **arg)
{
	write(STDERR_FILENO, av[0], _strlen(av[0]));
	write(STDERR_FILENO, ": ", 2);
	write_error_stderr(count);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, arg[0], _strlen(arg[0]));
	write(STDERR_FILENO, ": not found\n", 12);
}

/**
 * write_error_stderr - writes an error to stderr
 * @error: error to write
 * Return: number of characters written
 */

int write_error_stderr(int error)
{
	int temp, char_count = 0;
	unsigned int num;

	if (error < 0)
	{
		error = -error;
		write(2,"-", 1);
		char_count++;
	}

	num = error;
	while (num / 10)
	{
		char_count += write_error_stderr(num / 10);
	}

	temp = (num % 10) + '0';
	write(2, &temp, 1);
	char_count++;

	return (char_count);
}
