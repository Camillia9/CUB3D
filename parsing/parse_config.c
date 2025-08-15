/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:06:59 by camansou          #+#    #+#             */
/*   Updated: 2025/08/15 16:07:00 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Parse une ligne de configuration (texture ou couleur)
 */
static int	parse_config_element(char *trimmed, t_data *data)
{
	if (is_texture_line(trimmed))
	{
		parse_texture_line(trimmed, data);
		return (1);
	}
	if (is_color_line(trimmed))
	{
		parse_color_line(trimmed, data);
		return (1);
	}
	return (0);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!ft_strchr("01 NSEW", line[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * Vérifie que toutes les configurations sont complètes
 */
int	check_config_complete(t_data *data)
{
	if (!data->textures.north_path || !data->textures.south_path
		|| !data->textures.west_path || !data->textures.east_path)
		return (0);
	if (data->colors.floor_r == -1 || data->colors.floor_g == -1
		|| data->colors.floor_b == -1)
		return (0);
	if (data->colors.ceiling_r == -1 || data->colors.ceiling_g == -1
		|| data->colors.ceiling_b == -1)
		return (0);
	return (1);
}

int	parse_config_section(t_data *data)
{
	int		i;
	char	*line;

	i = 0;
	while (data->file_content[i])
	{
		line = trim_whitespace(data->file_content[i]);
		if (is_empty_line(line))
		{
			i++;
			continue ;
		}
		if (parse_config_element(line, data))
		{
			i++;
			continue ;
		}
		if (check_config_complete(data) && is_map_line(line))
			return (i);
		print_error("Invalid configuration line", data);
	}
	return (-1);
}
