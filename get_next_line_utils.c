/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 15:38:41 by egaziogl          #+#    #+#             */
/*   Updated: 2025/12/30 19:06:19 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strchr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i++] == c)
			return (i);
	}
	return (-1);
}

int	ft_strlen(char *s)
{
	int	i;
	
	i = 0;
	while (*(s++))
		i++;
	return (i);
}

// #include <stdio.h>

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*temp;
	size_t			bytes;
	void			*ptr;

	if (count > SIZE_MAX / size)
		return (NULL);
	if (count == 0 || size == 0)
		return (malloc(0));
	bytes = count * size;
	temp = malloc(bytes);
	if (!temp)
		return (NULL);
	ptr = (void *) temp;
	while (bytes--)
		*(temp++) = 0;
	return (ptr);
}

char	*ft_strnjoin(char *s1, char *s2, int n)
{
	char	*result;
	char	*temp;

	if (n < 0 || n > ft_strlen(s2))
		result = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	else
		result = ft_calloc((ft_strlen(s1) + n + 1), sizeof(char));
	if (!result)
		return (NULL);
	temp = result;
	while (*s1)
		*(temp++) = *(s1++);
	while (*s2 && n != 0)
	{
		*(temp++) = *(s2++);
		n--;
	}
	*temp = '\0';
	return (result);
}