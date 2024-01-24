/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dodordev <dodordev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:23:23 by dodordev          #+#    #+#             */
/*   Updated: 2024/01/23 15:49:21 by dodordev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>

int	main(void)
{
	int		fd1;
	int		fd2;
	int		fd3;
	int		fd4;
	char	*line;
	fd1 = open("fd1.txt", O_RDONLY);
	fd2 = open("fd2.txt", O_RDONLY);
	fd3 = open("fd3.txt", O_RDONLY);
	fd4 = open("fd4.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd1);
		printf("%s", line);
		if (line == NULL)
			break ;
		free(line);
		line = get_next_line(fd2);
		printf("%s", line);
		if (line == NULL)
			break ;
		free(line);
		line = get_next_line(fd3);
		printf("%s", line);
		if (line == NULL)
			break ;
		free(line);
		line = get_next_line(fd4);
		printf("%s", line);
		if (line == NULL)
			break ;
		free(line);
	}
	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);
	return (0);
}
