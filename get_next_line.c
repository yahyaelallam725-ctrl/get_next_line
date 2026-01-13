/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelallam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:15:27 by yelallam          #+#    #+#             */
/*   Updated: 2026/01/13 17:32:44 by yelallam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

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
	static char	*left_overs;
	ssize_t		bytes_read;

	char *line, *(nl_pos), *(buffer);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (handle_error(left_overs, -1));
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (handle_error(left_overs, -1));
	line = left_overs;
	left_overs = NULL;
	while (1)
	{
		nl_pos = ft_strchr(line, '\n');
		if (nl_pos)
		{
			process_line(&line, &left_overs, nl_pos);
			break ;
		}
		if (read_and_join(fd, &line, buffer, &bytes_read))
			break ;
	}
	free(buffer);
	return (line);
}
/*int main()
{
    int fd = open("file.txt", O_RDONLY);
    char *line;
    printf("%s", line = get_next_line(fd));
    free(line);
    printf("%s", line = get_next_line(fd));
    free(line);
    printf("%s", line = get_next_line(fd));
    free(line);

    close(fd);
}*/
