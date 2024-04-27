/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:33:21 by bschor            #+#    #+#             */
/*   Updated: 2024/02/12 15:29:35 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_free_gnl(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

static char	*ft_next(char *buffer, int *malloc_flag)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] != '\n')
		return (ft_free_gnl(&buffer), NULL);
	new = ft_calloc_gnl(ft_strlen_gnl(buffer) - i + 1, sizeof(char));
	if (!new)
	{
		*malloc_flag = 1;
		return (ft_free_gnl(&buffer), NULL);
	}
	while (buffer[++i])
		new[j++] = buffer[i];
	ft_free_gnl(&buffer);
	return (new);
}

static char	*ft_line(char *buffer, int	*malloc_flag)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_calloc_gnl(i + 1, sizeof(char));
	if (!line)
	{
		*malloc_flag = 1;
		return (NULL);
	}
	while (i-- > 0)
		line[i] = buffer[i];
	return (line);
}

static char	*ft_read(int fd, char *global_buf)
{
	char	*read_buffer;
	int		read_bytes;

	if (!global_buf)
		global_buf = ft_calloc_gnl(1, sizeof(char));
	if (!global_buf)
		return (NULL);
	read_buffer = ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
	if (!read_buffer)
		return (ft_free_gnl(&global_buf), NULL);
	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, read_buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (ft_free_gnl(&read_buffer), ft_free_gnl(&global_buf), NULL);
		read_buffer[read_bytes] = 0;
		global_buf = ft_strjoin_free(global_buf, read_buffer);
		if (!global_buf)
			return (ft_free_gnl(&read_buffer), NULL);
		if (ft_strchr_gnl(read_buffer, '\n'))
			read_bytes = 0;
	}
	ft_free_gnl(&read_buffer);
	return (global_buf);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line[OPEN_MAX];
	int			malloc_flag;

	malloc_flag = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (NULL);
	buffer[fd] = ft_read(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line[fd] = ft_line(buffer[fd], &malloc_flag);
	buffer[fd] = ft_next(buffer[fd], &malloc_flag);
	if (malloc_flag)
		return (ft_free_gnl(&buffer[fd]), ft_free_gnl(&line[fd]), NULL);
	return (line[fd]);
}
