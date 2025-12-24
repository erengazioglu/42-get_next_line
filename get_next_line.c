/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 15:27:28 by egaziogl          #+#    #+#             */
/*   Updated: 2025/12/24 01:03:09 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char* result;
	char	*result;
	char	*buf;
	int		bytes_read;

	buf = malloc(BUFFER_SIZE);
	if (!buf)
		return (NULL);
	bytes_read = 0;
	bytes_read += read(fd, buf, BUFFER_SIZE);

	return (buf);
}
