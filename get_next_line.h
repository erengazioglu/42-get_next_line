/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 15:27:50 by egaziogl          #+#    #+#             */
/*   Updated: 2026/01/07 11:21:38 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>

// utils
int		ft_strchr(char *s, char c);
int		ft_strlen(char *s);
char	*ft_strnjoin(char *s1, char *s2, ssize_t n, bool free_s1);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strcpy_lb(char *dst, char *src, char delim, bool lb);


// gnl
char	*get_next_line(int fd);

#endif