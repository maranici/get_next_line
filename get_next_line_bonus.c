/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:38:45 by macuesta          #+#    #+#             */
/*   Updated: 2024/11/13 17:12:59 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*buffer[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = fill_buffer(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = get_the_line(buffer[fd]);
	buffer[fd] = erase_from_buffer(buffer[fd]);
	return (line);
}

char	*fill_buffer(int fd, char *buffer)
{
	int		bytes_read;
	char	*tmp;

	bytes_read = 1;
	tmp = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	while (!ft_strchr(tmp, '\n') && bytes_read)
	{
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			if (buffer)
				free(buffer);
			if (tmp)
				free(tmp);
			return (NULL);
		}
		tmp[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, tmp);
	}
	free(tmp);
	return (buffer);
}

char	*get_the_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = (char *)ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*erase_from_buffer(char *buffer)
{
	int		i;
	int		j;
	char	*new_buf;

	i = 0;
	while (buffer && buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_buf = (char *)ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	if (!new_buf)
		return (NULL);
	i++;
	j = 0;
	while (buffer && buffer[i])
		new_buf[j++] = buffer[i++];
	new_buf[j] = '\0';
	free(buffer);
	return (new_buf);
}
