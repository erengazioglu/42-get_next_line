/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 15:27:28 by egaziogl          #+#    #+#             */
/*   Updated: 2026/01/06 23:38:52 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*init_stash(char *stash)
{
	char	*new_stash;
	int		lb_pos;

	if (!stash)
	{
		stash = ft_calloc(BUFFER_SIZE, 1);
		if (!stash)
			return (NULL);
		return (stash);
	}
	lb_pos = ft_strchr(stash, '\n');
	if (lb_pos == -1)
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_calloc(ft_strlen(stash + lb_pos), 1);
	if (!new_stash)
	{
		free(stash);
		return (NULL);
	}
	ft_strcpy_lb(new_stash, stash + lb_pos + 1, '\0', false);
	free(stash);
	return (new_stash);
}

bool	init(int fd, char **stash, char **buffer, int *bytes_read)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (false);
	*stash = init_stash(*stash);
	if (!(*stash))
		return (false);
	*buffer = ft_calloc(BUFFER_SIZE, 1);
	if (!(*buffer))
	{
		free(*stash);
		return (false);
	}
	*bytes_read = read(fd, *buffer, BUFFER_SIZE);
	if (!(*bytes_read))
	{
		free(*buffer);
		free(*stash);
		return (false);
	}
	return (true);
}

char	*build_stash(char **stash, char *buffer, int lb_pos)
{
	char	*result;
	char	*result_base;
	char	*buffer_base;
	
	result = ft_calloc(ft_strlen(*stash) + ft_strlen(buffer) + 2, 1);
	if (!result)
	{
		free(*stash);
		free(buffer);
		return (NULL);
	}
	result_base = result;
	buffer_base = buffer;
	result = ft_strcpy_lb(result, *stash, '\0', false);
	result = ft_strcpy_lb(result, buffer, '\n', true);
	while (*buffer != '\n')
		buffer++;
	result++;
	result = ft_strcpy_lb(result, ++buffer, '\0', false);
	free(buffer_base);
	free(*stash);
	*stash = result_base;
	return (*stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	int			bytes_read;
	int			lb_pos;

	if (!init(fd, &stash, &buffer, &bytes_read))
		return (NULL);
	lb_pos = ft_strchr(buffer, '\n');
	while (bytes_read == BUFFER_SIZE && lb_pos == -1)
	{
		stash = ft_strnjoin(stash, buffer, -1, true);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		lb_pos = ft_strchr(buffer, '\n');
	}
	if (lb_pos != -1)
		return (build_stash(&stash, buffer, lb_pos)); // this will free buffer and add \0
	stash = ft_strnjoin(stash, buffer, -1, true);
	free(buffer);
	return (stash);
}
