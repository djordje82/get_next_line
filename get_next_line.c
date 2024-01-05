/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dodordev <dodordev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 09:39:59 by dodordev          #+#    #+#             */
/*   Updated: 2024/01/05 13:56:54 by dodordev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*fill_buffer(int fd, char *left_c, char *buffer);
static char	*set_line(char *line);
static char	*ft_strchr(char *s, int c);
static int	is_valid_fd(int fd);

static int	is_valid_fd(int fd)
{
	return (fd >= 0 && BUFFER_SIZE > 0 && read(fd, 0, 0) >= 0);
}

char	*get_next_line(int fd)
{
	static char	*upend_char;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!is_valid_fd(fd) || !buffer)
	{
		free(upend_char);
		free(buffer);
		upend_char = NULL;
		return (NULL);
	}
	line = fill_buffer(fd, upend_char, buffer);
	free(buffer);
	if (!line)
		return (NULL);
	upend_char = set_line(line);
	return (line);
}

static char	*fill_buffer(int fd, char *upend_char, char *buffer)
{
	ssize_t	buffer_read;
	char	*tmp;

	buffer_read = 1;
	while (buffer_read > 0)
	{
		buffer_read = read(fd, buffer, BUFFER_SIZE);
		if (buffer_read == -1)
		{
			free(upend_char);
			return (NULL);
		}
		else if (buffer_read == 0)
			break ;
		buffer[buffer_read] = 0;
		if (!upend_char)
			upend_char = ft_strdup("");
		tmp = upend_char;
		upend_char = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (upend_char);
}

static char	*set_line(char *line_buffer)
{
	char	*upend_char;
	ssize_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == 0 || line_buffer[1] == 0)
		return (NULL);
	upend_char = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*upend_char == 0)
	{
		free(upend_char);
		upend_char = NULL;
	}
	line_buffer[i + 1] = 0;
	return (upend_char);
}

static char	*ft_strchr(char *s, int c)
{
	unsigned int	i;
	char			cc;

	i = 0;
	cc = (char)c;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == cc)
		return ((char *)&s[i]);
	return (NULL);
}
