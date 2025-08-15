/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:06:49 by camansou          #+#    #+#             */
/*   Updated: 2025/08/15 16:06:53 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Libère la mémoire des chemins de textures
 */
void	free_textures(t_textures *textures)
{
	if (textures->north_path)
	{
		free(textures->north_path);
		textures->north_path = NULL;
	}
	if (textures->south_path)
	{
		free(textures->south_path);
		textures->south_path = NULL;
	}
	if (textures->west_path)
	{
		free(textures->west_path);
		textures->west_path = NULL;
	}
	if (textures->east_path)
	{
		free(textures->east_path);
		textures->east_path = NULL;
	}
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	free_textures(&data->textures);
	free_map(&data->map);
	free_file_content_from_data(data);
	free(data);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map->grid)
		return ;
	i = 0;
	while (i < map->height && map->grid[i])
	{
		free(map->grid[i]);
		map->grid[i] = NULL;
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}

/**
 * Libère le contenu du fichier stocké dans data
 */
void	free_file_content_from_data(t_data *data)
{
	int	i;

	if (!data || !data->file_content)
		return ;
	i = 0;
	while (data->file_content[i])
	{
		free(data->file_content[i]);
		i++;
	}
	free(data->file_content);
	data->file_content = NULL;
}
