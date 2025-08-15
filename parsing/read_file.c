/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:07:14 by camansou          #+#    #+#             */
/*   Updated: 2025/08/15 16:20:20 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../Libft/get_next_line/get_next_line.h"

/**
 * Convertit la liste en tableau de strings
 */
static char	**convert_list_to_array(t_list *temp_lines, int line_count,
		t_data *data)
{
	char	**file_content;
	t_list	*current;
	int		i;

	file_content = malloc(sizeof(char *) * (line_count + 1));
	if (!file_content)
		print_error("Memory allocation failed", NULL);
	current = temp_lines;
	i = 0;
	while (current && i < line_count)
	{
		file_content[i] = ft_strdup((char *)current->content);
		if (!file_content[i])
			print_error("Memory allocation failed for file content", data);
		current = current->next;
		i++;
	}
	file_content[i] = NULL;
	return (file_content);
}

static void	read_file_lines(t_data *data, int fd)
{
	t_list	*lines;
	char	*trimmed;
	char	*line;
	int		count;

	lines = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		trimmed = ft_strtrim(line, "\n");
		free(line);
		ft_lstadd_back(&lines, ft_lstnew(trimmed));
		line = get_next_line(fd);
	}
	if (!lines)
		print_error("Empty file", data);
	count = ft_lstsize(lines);
	data->file_content = convert_list_to_array(lines, count, data);
	ft_lstclear(&lines, free);
}

static void	parse_config_and_map(t_data *data)
{
	int	map_start;

	map_start = parse_config_section(data);
	if (!check_config_complete(data))
		print_error("Incomplete configuration", data);
	parse_map_section(data, map_start);
}

void	parse_file(t_data *data, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		print_error("Cannot open file", data);
	read_file_lines(data, fd);
	close(fd);
	parse_config_and_map(data);
}
