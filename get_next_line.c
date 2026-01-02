/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 15:27:28 by egaziogl          #+#    #+#             */
/*   Updated: 2026/01/02 07:55:53 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*result;
	char		*buffer;
	char		*swap;
	int			bytes_read;
	int			lb_pos;

	buffer = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!buffer)
		return (NULL);
	if (!result)
		result = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!result)
	{
		free(buffer);
		return (NULL);
	}
	
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	lb_pos = ft_strchr(buffer, '\n');
	while (bytes_read == BUFFER_SIZE && lb_pos == -1)
	{
		swap = ft_strnjoin(result, buffer, -1);
		free(result);
		result = swap;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		lb_pos = ft_strchr(buffer, '\n');
	}

	swap = ft_strnjoin(result, buffer, lb_pos);
	free(buffer);
	free(result);
	result = swap;
	return (result);
}
