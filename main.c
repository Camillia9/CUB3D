/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:07:45 by camansou          #+#    #+#             */
/*   Updated: 2025/08/15 16:33:54 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <string.h>

static int	free_init_mlx(t_data *data)
{
	if (!init_mlx(data))
	{
		printf("Error: init_mlx failed\n");
		free_data(data);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	validate_arguments(argc, argv);
	data = init_data();
	parse_file(data, argv[1]);
	validate_map(data);
	free_init_mlx(data);
	init_player(&data->player, &data->map);
	if (!load_all_textures(data))
	{
		printf("Error: Failed to load textures\n");
		close_game(data);
		return (1);
	}
	render_frame (data);
	mlx_hook (data->mlx.win, 2, 1L << 0, handle_keypress, data);
	mlx_hook (data->mlx.win, 3, 1L << 1, handle_keyrelease, data);
	mlx_hook (data->mlx.win, 17, 1L << 17, close_game, data);
	mlx_loop_hook (data->mlx.mlx, game_loop, data);
	mlx_loop (data->mlx.mlx);
	close_game(data);
	free_data(data);
	return (0);
}
