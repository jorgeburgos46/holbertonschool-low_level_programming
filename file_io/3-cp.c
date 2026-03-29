#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * close_fd - closes a file descriptor
 * @fd: file descriptor to close
 */
void close_fd(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * exit_error - prints an error message and exits
 * @code: exit code
 * @filename: name of the file
 */
void exit_error(int code, char *filename)
{
	if (code == 97)
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
	else if (code == 98)
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", filename);
	else if (code == 99)
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", filename);

	exit(code);
}

/**
 * copy_file - copies content from one file to another
 * @fd_from: source file descriptor
 * @fd_to: destination file descriptor
 * @file_from: source file name
 * @file_to: destination file name
 */
void copy_file(int fd_from, int fd_to, char *file_from, char *file_to)
{
	ssize_t letters_read, letters_written;
	char buffer[1024];

	letters_read = read(fd_from, buffer, 1024);
	while (letters_read > 0)
	{
		letters_written = write(fd_to, buffer, letters_read);
		if (letters_written != letters_read)
		{
			close_fd(fd_from);
			close_fd(fd_to);
			exit_error(99, file_to);
		}
		letters_read = read(fd_from, buffer, 1024);
	}

	if (letters_read == -1)
	{
		close_fd(fd_from);
		close_fd(fd_to);
		exit_error(98, file_from);
	}
}

/**
 * main - copies the content of a file to another file
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	int fd_from, fd_to;

	if (argc != 3)
		exit_error(97, NULL);

	fd_from = open(argv[1], O_RDONLY);
	if (fd_from == -1)
		exit_error(98, argv[1]);

	fd_to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		close_fd(fd_from);
		exit_error(99, argv[2]);
	}

	copy_file(fd_from, fd_to, argv[1], argv[2]);
	close_fd(fd_from);
	close_fd(fd_to);

	return (0);
}
