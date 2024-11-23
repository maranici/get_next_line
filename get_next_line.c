/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:23:22 by macuesta          #+#    #+#             */
/*   Updated: 2024/11/13 17:12:51 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = fill_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_the_line(buffer);
	buffer = erase_from_buffer(buffer);
	return (line);
}

char	*fill_buffer(int fd, char *buffer)
{
	int		bytes_read;
	char	*tmp;

	tmp = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	bytes_read = 1;
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
	if (!buffer || buffer[i] == '\0')
		return (NULL);
	while (buffer && buffer[i] && buffer[i] != '\n')
		i++;
	line = (char *)ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer && buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer && buffer[i] && buffer[i] == '\n')
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
