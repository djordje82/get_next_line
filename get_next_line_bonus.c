/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dodordev <dodordev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:25:07 by dodordev          #+#    #+#             */
/*   Updated: 2024/01/04 13:57:51 by dodordev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*fill_buffer(int fd, char *left_c, char *buffer);
static char	*set_line(char *line);
static char	*ft_strchr(char *s, int c);

char	*get_next_line(int fd)
{
	static char	*upend_char[MAX_FD];
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(upend_char[fd]);
		free(buffer);
		upend_char[fd] = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = fill_buffer(fd, upend_char[fd], buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	upend_char[fd] = set_line(line);
	return (line);
}

static char	*read_and_concatenate(int fd, char *upend_char, char *buffer)
{
	size_t	buffer_read;
	char	*temp;

	buffer_read = read(fd, buffer, BUFFER_SIZE);
	if (buffer_read <= 0)
		return (NULL);
	buffer[buffer_read] = '\0';
	temp = ft_strjoin(upend_char, buffer);
	if (temp == NULL)
		return (NULL);
	return (temp);
}

static char	*fill_buffer(int fd, char *upend_char, char *buffer)
{
	char	*temp;

	while (1)
	{
		temp = read_and_concatenate(fd, upend_char, buffer);
		if (temp == NULL)
		{
			free(upend_char);
			return (NULL);
		}
		free(upend_char);
		upend_char = temp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (upend_char);
}

/*
static char	*fill_buffer(int fd, char *upend_char, char *buffer)
{
	size_t	buffer_read;
	char	temp;

	buffer_read = 1;
	while (buffer_read > 0)
	{
		buffer_read = read(fd, buffer, BUFFER_SIZE);
		if (buffer_read <= 0)
			break ;
	buffer[buffer_read] = '\0';
	temp = ft_strjoin(upend_char, buffer);
	{
		if (temp != NULL)
		{
			free(upend_char);
			upend_char = temp;
		}
		else
		{
			free(buffer);
			free(upend_char);
			return (NULL);
		}
	}
	if (ft_strchr(buffer, '\n'))
		break ;
	}
	return (upend_char);
}

static char	*fill_buffer(int fd, char *upend_char, char *buffer)
{
	ssize_t	buffer_read;
	char	*temp;
	size_t	upend_len;

	upend_len = ft_strlen(upend_char);
	buffer_read = 1;
	while (buffer_read > 0)
	{
		buffer_read = read(fd, buffer, BUFFER_SIZE);
		if (buffer_read <= 0)
			break ;
		buffer[buffer_read] = '\0';
		temp = (char *)malloc((upend_len + buffer_read + 1) * sizeof(char));
		if (!temp)
		{
			free(upend_char);
			return (NULL);
		}
		ft_strcpy(temp, upend_char);
		ft_strcat(temp, buffer);
		upend_char = temp;
		upend_len += buffer_read;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (upend_char);
}
*/

static char	*set_line(char *line_buffer)
{
	char	*upend_char;
	ssize_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == '\0' || line_buffer[i + 1] == '\0')
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
