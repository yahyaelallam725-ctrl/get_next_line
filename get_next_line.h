/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelallam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:27:45 by yelallam          #+#    #+#             */
/*   Updated: 2026/01/10 15:14:31 by yelallam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 7
# endif

char	*get_next_line(int fd);
char	*ft_strchr(char *s, int c);
char	*ft_extract_str(char *start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);

#endif