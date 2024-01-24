/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dodordev <dodordev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:53:17 by dodordev          #+#    #+#             */
/*   Updated: 2024/01/23 16:04:31 by dodordev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFF_SIZE 8

// Assuming get_next_line function is defined elsewhere
char *get_next_line(int fd);
void	test_from_stdin(int num_lines, int line_length)
{
	char	*line;

	printf("Testing from standard input: %d lines of %d characters each\n",
		num_lines, line_length);
	for (int i = 0; i < num_lines; i++)
	{
		line = get_next_line(STDIN_FILENO);
		if (line)
		{
			printf("Line %d: %s\n", i + 1, line);
			free(line);
		}
	}
}
void	test_from_file(const char *filename, int num_lines, int line_length)
{
	int		fd;
	char	*line;

	printf("Testing from file '%s': %d lines of %d characters each\n", filename,
		num_lines, line_length);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return ;
	}
	for (int i = 0; i < num_lines; i++)
	{
		line = get_next_line(fd);
		if (line)
		{
			printf("Line %d: %s\n", i + 1, line);
			free(line);
		}
	}
	close(fd);
}
void	error_management_test(void)
{
	char	*line;

	printf("Error management test with invalid file descriptor\n");
	line = get_next_line(42);
	if (line == NULL)
	{
		printf("Error correctly handled\n");
	}
	else
	{
		printf("Error not handled as expected\n");
		free(line);
	}
}
int	main(int argc, char *argv[])
{
	// Basic Tests
	test_from_stdin(3, 8);
	test_from_file("test1.txt", 3, 8);
	// Middle Tests
	test_from_file("test1.txt", 3, 16);
	test_from_stdin(3, 16);
	// Advanced Tests
	test_from_file("test1.txt", 3, 4);
	test_from_stdin(3, 4);
	// Error Management
	error_management_test();
	return (0);
}
