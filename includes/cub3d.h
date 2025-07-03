#ifndef CUB3D_H
# define CUB3D_H

#include "../Libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "structures.h"
#include "mlx.h"
#include <fcntl.h>

//MLX
int	init_mlx(t_data *data);
int	handle_keypress(int keycode, t_data *data);
int handle_keyrelease(int keycode, t_data *data);
int game_loop(t_data *data);
void fill_screen(t_data *data, int color);
int	load_texture(t_data *data, t_texture *texture, char *path);
int load_all_textures(t_data *data);


//Free
int close_game(t_data *data);
void free_texture(t_data *data, t_texture *texture);
void free_all_textures(t_data *data);

//TEST


//check_file
void print_error(const char *message);
int check_file_extension(char *filename);
int check_file_access(char *filename);
void validate_arguments(int argc, char **argv);


#endif