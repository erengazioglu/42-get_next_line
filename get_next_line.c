/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 15:27:28 by egaziogl          #+#    #+#             */
/*   Updated: 2025/12/30 19:29:16 by egaziogl         ###   ########.fr       */
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

	// init
	buffer = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!buffer)
		return (NULL);
	result = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!result)
	{
		free(buffer);
		return (NULL);
	}
	
	// first read
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	lb_pos = ft_strchr(buffer, '\n');
	// printf("bytes read: %d\n", bytes_read);
	// printf("lb_pos: %d\n", lb_pos);

	while (bytes_read == BUFFER_SIZE && lb_pos == -1)
	{
		swap = ft_strnjoin(result, buffer, -1);
		free(result);
		result = swap;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		lb_pos = ft_strchr(buffer, '\n');
	}
	swap = ft_strnjoin(result, buffer, lb_pos);
	free(result);
	result = swap;

	// // subsequent reads
	// while (bytes_read == BUFFER_SIZE)
	// {
	// 	swap = ft_strnjoin(result, buffer, -1);
	// 	free(result);
	// 	result = swap;
	// 	bytes_read += read(fd, buffer, BUFFER_SIZE);
	// 	lb_pos = ft_strchr(buffer, '\n');
	// }
	
	// // final read
	// if (lb_pos != -1)
	// {
	// 	swap = ft_strnjoin(result, buffer, lb_pos);
	// 	free(result);
	// 	result = swap;
	// }

	free(buffer);
	return (result);
}
