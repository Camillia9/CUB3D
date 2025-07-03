/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:15:56 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 11:45:10 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*process_buffer(char *line, char *buffer, int bytes_read)
{
	char	*temp;

	if (bytes_read <= 0 || !buffer)
		return (line);
	buffer[bytes_read] = '\0';
	if (!line)
		return (gnl_strdup(buffer));
	temp = gnl_strjoin(line, buffer);
	free(line);
	return (temp);
}

char	*save_remainder(char *line)
{
	char	*remainder;
	int		i;
	int		j;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
		return (NULL);
	remainder = malloc(gnl_strlen(line) - i + 1);
	if (!remainder)
		return (NULL);
	i++;
	j = 0;
	while (line[i])
		remainder[j++] = line[i++];
	remainder[j] = '\0';
	return (remainder);
}

char	*extract_line(char *str)
{
	int		i;
	char	*line;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*read_line(int fd, char *line, char *remainder)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (remainder)
		line = gnl_strdup(remainder);
	while (!line || !gnl_strchr(line, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(line);
			return (NULL);
		}
		line = process_buffer(line, buffer, bytes_read);
		if (!line || bytes_read == 0)
			break ;
	}
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*result;
	static char	*remainder;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(remainder), NULL);
	line = NULL;
	if (remainder)
	{
		line = gnl_strdup(remainder);
		free(remainder);
		remainder = NULL;
	}
	line = read_line(fd, line, NULL);
	if (!line || line[0] == '\0')
	{
		if (line)
			free(line);
		return (NULL);
	}
	remainder = save_remainder(line);
	result = extract_line(line);
	free(line);
	return (result);
}
// int	main(int ac, char **av)
// {
// 	int		fd;
// 	char	*str;

// 	if (ac != 2)
// 		return (1);
// 	fd = open(av[1], O_RDONLY);
// 	if (fd == -1)
// 		return (1);
// 	// while ((str = get_next_line(fd)) != NULL)
// 	// {
// 	// 	printf("%s", str);
// 	// 	free(str);
// 	// }
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	close(fd);
// 	// fd = open(av[1], O_RDONLY);
// 	// if (fd == -1)
// 	// 	return (1);
// 	// printf("%s", get_next_line(fd));
// 	// close(fd);
// 	return (0);
// }
