#include "../includes/cub3d.h"
#include <string.h>

int	main(int argc, char **argv)
{
	t_data	*data;

	validate_arguments(argc, argv);
	data = init_data();
	parse_file(data, argv[1]);
	validate_map(data);
	print_config_data(data);

	// Tester init_mlx
	printf("🚀 Testing init_mlx...\n");
	
	if (!init_mlx(data))
	{
	    printf("❌ Error: init_mlx failed\n");
	    free(data);
	    return (1);
	}
	//init_map(data);
	init_player(&data->player, &data->map);

	if (!load_all_textures(data))
	{
	    printf("❌ Error: Failed to load textures\n");
	    close_game(data);
	    return (1);
	}
	render_frame(data);

	//fill_screen(data, 0x000000);  // Noir
	//// Dessiner le rayon
	//test_rayon_visual(data);
	//// Afficher
	//mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	
	// Setup des événements pour pouvoir fermer
	//mlx_loop_hook(data->mlx.mlx, game_loop, data);
	mlx_hook(data->mlx.win, 2, 1L<<0, handle_keypress, data);    // KeyPress
	mlx_hook(data->mlx.win, 3, 1L<<1, handle_keyrelease, data); // Keyrelease
	mlx_hook(data->mlx.win, 17, 1L<<17, close_game, data);     // Close button
	
	// Lancer la boucle
	mlx_loop_hook(data->mlx.mlx, game_loop, data);
	mlx_loop(data->mlx.mlx);

	free_data(data);
	return (0);
	
}
