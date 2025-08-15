/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:06:54 by camansou          #+#    #+#             */
/*   Updated: 2025/08/15 16:06:55 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../Libft/get_next_line/get_next_line.h"

/**
 * Initialise les structures de configuration
 * Initialiser les textures
 * Initialiser les couleurs avec -1 (non définies)
 * Initialiser d'autres valeurs par défaut si nécessaire
 */
static void	init_default_values(t_data *data)
{
	data->textures.north_path = NULL;
	data->textures.south_path = NULL;
	data->textures.west_path = NULL;
	data->textures.east_path = NULL;
	data->colors.floor_r = -1;
	data->colors.floor_g = -1;
	data->colors.floor_b = -1;
	data->colors.ceiling_r = -1;
	data->colors.ceiling_g = -1;
	data->colors.ceiling_b = -1;
	data->colors.floor_color = 0;
	data->colors.ceiling_color = 0;
	data->screen_width = 800;
	data->screen_height = 600;
	data->running = 1;
	data->map.player_x = -1;
	data->map.player_y = -1;
	data->map.player_dir = 0;
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		print_error("Memory allocation failed", NULL);
	ft_memset(data, 0, sizeof(t_data));
	init_default_values(data);
	return (data);
}
