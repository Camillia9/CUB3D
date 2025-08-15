/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:06:35 by camansou          #+#    #+#             */
/*   Updated: 2025/08/15 16:06:37 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_temp_grid(char **grid, int height)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (i < height)
	{
		if (grid[i])
			free(grid[i]);
		i++;
	}
	free(grid);
}

char	**duplicate_grid(t_data *data)
{
	char	**temp;
	int		i;

	temp = malloc(sizeof(char *) * (data->map.height + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (i < data->map.height)
	{
		temp[i] = ft_strdup(data->map.grid[i]);
		if (!temp[i])
		{
			free_temp_grid(temp, i);
			return (NULL);
		}
		i++;
	}
	temp[i] = NULL;
	return (temp);
}

static char	*create_normalized_line(char *line, int target_width, t_data *data)
{
	char	*normalized;
	int		i;
	int		line_len;

	line_len = get_line_length_without_newline(line);
	normalized = malloc(target_width + 1);
	if (!normalized)
		print_error("Memory allocation failed", data);
	i = 0;
	while (i < line_len && i < target_width)
	{
		normalized[i] = line[i];
		i++;
	}
	while (i < target_width)
	{
		normalized[i] = '2';
		i++;
	}
	normalized[i] = '\0';
	return (normalized);
}

void	fill_map_grid(t_data *data, int start)
{
	int		i;
	int		row;
	char	*line;

	i = start;
	row = 0;
	while (row < data->map.height && data->file_content[i])
	{
		line = data->file_content[i];
		if (!is_valid_map_line(line))
			break ;
		data->map.grid[row] = create_normalized_line(line, data->map.width,
				data);
		row++;
		i++;
	}
	data->map.grid[row] = NULL;
}
