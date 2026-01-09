/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 15:38:41 by egaziogl          #+#    #+#             */
/*   Updated: 2026/01/09 14:03:51 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strfind(char *s, char c)
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

	if (!s)
		return (0);
	i = 0;
	while (*(s++))
		i++;
	return (i);
}

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

char	*ft_strnjoin(char *s1, char *s2, ssize_t n, bool free_s1)
{
	char	*result;
	char	*result_base;
	char	*s1_base;
	int		s1_len;
	int		s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (n < 0 || n > s2_len)
		result = ft_calloc((s1_len + s2_len + 1), sizeof(char));
	else
		result = ft_calloc((s1_len + n + 1), sizeof(char));
	if (!result)
		return (NULL);
	result_base = result;
	s1_base = s1;
	while (*s1)
		*(result++) = *(s1++);
	while (*s2 && n-- != 0)
		*(result++) = *(s2++);
	*result = '\0';
	if (free_s1)
		free(s1_base);
	return (result_base);
}

// returns the null character at the end, super hacky
char	*ft_strcpy_lb(char *dst, char *src, char delim, bool lb)
{
	while (*src != delim)
		*dst++ = *src++;
	if (lb)
		*dst++ = '\n';
	*dst = '\0';
	return (dst);
}
