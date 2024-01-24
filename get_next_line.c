/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dodordev <dodordev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 09:39:59 by dodordev          #+#    #+#             */
/*   Updated: 2024/01/24 16:02:56 by dodordev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	copy_newline_to_buf(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}

static int	find_line(char *buf, char **line)
{
	int		i;
	int		j;
	int		flag_line;
	char	*find_line;

	i = 0;
	j = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	flag_line = 0;
	if (buf[i] == '\n')
		flag_line = 1;
	find_line = ft_calloc(i + flag_line + 1, 1);
	if (find_line == NULL)
		return (-1);
	while (j < i + flag_line)
	{
		find_line[j] = buf[j];
		j++;
	}
	*line = ft_strjoin(*line, find_line);
	if (*line == NULL)
		return (-1);
	copy_newline_to_buf(buf, &buf[i + flag_line]);
	return (flag_line);
}

static char	*free_line(char **line)
{
	if (*line != NULL)
		free(*line);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	int			count_bytes;
	int			flag_line;

	line = NULL;
	flag_line = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_FD)
		return (NULL);
	while (flag_line == 0)
	{
		flag_line = find_line(buf, &line);
		if (flag_line == -1)
			return (free_line(&line));
		if (flag_line == 0)
		{
			count_bytes = read(fd, buf, BUFFER_SIZE);
			if (count_bytes == 0 && *line)
				flag_line = 1;
			else if (count_bytes <= 0)
				return (free_line(&line));
			buf[count_bytes] = '\0';
		}
	}
	return (line);
}
