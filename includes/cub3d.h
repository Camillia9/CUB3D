#ifndef CUB3D_H
# define CUB3D_H

#include "../Libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include "structures.h"
#include "mlx.h"

// Map
#define MAP_SIZE 20

// WASD
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115 
#define KEY_D 100

// Flèches
#define KEY_LEFT 65361
#define KEY_RIGHT 65363

//MLX
int	init_mlx(t_data *data);
int	handle_keypress(int keycode, t_data *data);
int handle_keyrelease(int keycode, t_data *data);
void	handle_mouvement(t_data *data);
void	handle_mouvement_2(t_data *data);
int game_loop(t_data *data);
void fill_screen(t_data *data, int color);
int	load_texture(t_data *data, t_texture *texture, char *path);
int load_all_textures(t_data *data);
void init_player(t_player *player);
void move_forward(t_data *data);
void	move_backward(t_data *data);
void	move_left(t_data *data);
void	move_right(t_data *data);
void	rotate_left(t_data *data);
void	rotate_right(t_data *data);

//Free
int close_game(t_data *data);
void free_texture(t_data *data, t_texture *texture);
void free_all_textures(t_data *data);

//TEST
int is_wall(int x, int y);
void    render_frame(t_data *data);

void cast_ray(t_ray *ray, double start_x, double start_y, double dir_x, double dir_y);
void	render_scene(t_data *data);

//check_file
void print_error(const char *message);
int check_file_extension(char *filename);
int check_file_access(char *filename);
void validate_arguments(int argc, char **argv);

//check_texture
int check_texture_file(char *path);
void parse_texture(t_data *data, char *line);


#endif