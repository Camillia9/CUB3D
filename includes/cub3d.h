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
void init_player(t_player *player, t_map *map);
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

//init data
t_data	*init_data(void);

//read file
void	parse_file(t_data *data, char *filename);

//parse config
int	is_map_line(char *line);
int check_config_complete(t_data *data);
int	parse_config_section(t_data *data);


void	parse_map_section(t_data *data, int start_index);
void allocate_map_grid(t_data *data);
void	fill_map_grid(t_data *data, int start);

void	validate_map(t_data *data);
int	validate_map_closure(t_data *data);
void	free_temp_grid(char **grid, int height);
char	**duplicate_grid(t_data *data);
int	flood_fill_check(char **grid, int x, int y, t_data *data);
int	get_line_length_without_newline(char *line);

//check_file
void print_error(char *message, t_data *data);
//int check_file_extension(char *filename);
int check_file_access(char *filename);
void validate_arguments(int argc, char **argv);

//check map
int	validate_map_closure(t_data *data);


//utils map

int	is_valid_map_line(char *line);
void	count_map_elements(t_data *data, int *player_count, int *empty_spaces);


//parsing utils
int is_texture_line(char *line);
int is_color_line(char *line);
char *trim_whitespace(char *str);
char *skip_whitespace(char *line);
int is_empty_line(char *line);
void	*safe_malloc(t_data *data, size_t size);

int identify_texture_type(char *line, t_data *data);
char *extract_texture_path(char *line, t_data *data);
void assign_texture_to_data(t_data *data, char *path, int texture_type);
int parse_texture_line(char *line, t_data *data);




//parse colors
int		parse_rgb_value(char **str);
int		identify_color_type(char *line, t_data *data);
void	parse_rgb_values(char *color_start, t_data *data, int color_type);
int		parse_color_line(char *line, t_data *data);

//fill colors
void	assign_rgb_values(t_data *data, int rgb[3], int color_type);
void	assign_floor_color(t_data *data, int rgb[3]);
void	assign_ceiling_color(t_data *data, int rgb[3]);
int		encode_rgb_color(int r, int g, int b);

//player
void	find_player_position(t_data *data);
//void	find_player_position(t_data *data, int *x, int *y);
int is_player_char(char c);

//free
void	free_textures(t_textures *textures);
void	free_data(t_data *data);
void	free_map(t_map *map);
void	free_file_content_from_data(t_data *data);

//debug
void	print_config_data(t_data *data);
void	print_map(char **map);

//TEST
int is_wall(t_data *data, int x, int y);
void    render_frame(t_data *data);

void cast_ray(t_ray *ray, t_ray_params *params, t_data *data);
void	render_scene(t_data *data);
void	init_direction_ns(t_player *player, t_map *map);
void	init_direction_ew(t_player *player, t_map *map);

t_texture	*select_wall_texture(t_ray *ray, t_data *data);
int	calcul_tex_x(t_ray *ray, t_texture *texture, double start_x,
		double start_y);
int	calculate_tex_y(t_ray *ray, t_data *data, int y, t_texture *texture);

//check_texture
int check_texture_file(char *path);
void parse_texture(t_data *data, char *line);


#endif