/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelallam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:13:29 by yelallam          #+#    #+#             */
/*   Updated: 2026/01/16 17:59:30 by yelallam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

static char	*handle_extraction(char **line, char *nl_pos)
{
	char	*next_left_overs;
	char	*tmp_line;
	size_t	len;

	next_left_overs = NULL;
	if (*(nl_pos + 1) != '\0')
		next_left_overs = ft_extract_str(nl_pos + 1, ft_strlen(nl_pos + 1));
	len = (nl_pos - *line) + 1;
	tmp_line = ft_extract_str(*line, len);
	free(*line);
	*line = tmp_line;
	return (next_left_overs);
}

static char	*handle_error(char *line, ssize_t bytes_read)
{
	if (bytes_read == -1)
	{
		if (line)
			free(line);
		return (NULL);
	}
	else
		return (line);
}

static void	process_line(char **line, char **left_overs, char *nl_pos)
{
	*left_overs = handle_extraction(line, nl_pos);
}

static int	read_and_join(int fd, char **line,
	char *buffer, ssize_t *bytes_read)
{
	char	*tmp;

	*bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (*bytes_read <= 0)
	{
		*line = handle_error(*line, *bytes_read);
		return (1);
	}
	buffer[*bytes_read] = '\0';
	tmp = ft_strjoin(*line, buffer);
	free(*line);
	*line = tmp;
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*left_overs[1024];
	ssize_t		bytes_read;

	char *line, *(nl_pos), *(buffer);
	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (handle_error(left_overs[fd], -1));
	line = left_overs[fd];
	left_overs[fd] = NULL;
	while (1)
	{
		nl_pos = ft_strchr(line, '\n');
		if (nl_pos)
		{
			process_line(&line, &left_overs[fd], nl_pos);
			break ;
		}
		if (read_and_join(fd, &line, buffer, &bytes_read))
			break ;
	}
	free(buffer);
	return (line);
}
