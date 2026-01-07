/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 15:27:28 by egaziogl          #+#    #+#             */
/*   Updated: 2026/01/07 17:13:30 by egaziogl         ###   ########.fr       */
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
	lb_pos = ft_strfind(stash, '\n');
	if (lb_pos == -1)
		return (free(stash), stash = NULL, NULL);
	new_stash = ft_calloc(ft_strlen(stash + lb_pos + 1) + 2, 1);
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
	int	i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (false);
	*stash = init_stash(*stash);
	if (!(*stash))
		return (false);
	*buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!(*buffer))
	{
		free(*stash);
		return (false);
	}
	ft_strcpy_lb(*buffer, *stash, '\0', false);
	*bytes_read = BUFFER_SIZE;
	i = 0;
	while ((*stash)[i])
		(*stash)[i++] = '\0';
	return (true);
}

char	*build_stash(char **stash, char *buffer)
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
	if (!(*buffer))
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	lb_pos = ft_strfind(buffer, '\n');
	while (bytes_read == BUFFER_SIZE && lb_pos == -1)
	{
		stash = ft_strnjoin(stash, buffer, -1, true);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		lb_pos = ft_strfind(buffer, '\n');
	}
	if (lb_pos != -1)
		return (build_stash(&stash, buffer));
	stash = ft_strnjoin(stash, buffer, -1, true);
	free(buffer);
	return (stash);
}
