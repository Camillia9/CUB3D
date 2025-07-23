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
void	init_default_values(t_data *data);
int count_lines(const char *filename);
char **read_file_into_array(const char *filename);

//check_file
void print_error(char *message, t_data *data);
int check_file_extension(char *filename);
int check_file_access(char *filename);
void validate_arguments(int argc, char **argv);

//parse_config
void	read_and_parse_config(t_data *data, char *filename);
void	parse_configuration(t_data *data);
void	parse_map_from_lines(char **map_lines, t_data *data);

//read_file
char	**read_entire_file(char *filename, t_data *data);
void	free_file_content(char **file_content);

//check_texture
char	*fill_line(char *line, int width, t_data *data);
int	check_xpm_extension(char *filename);

//check map
void	validate_complete_map(t_data *data);
void	validate_map_basic(t_data *data);
int	validate_map_closure(t_data *data);
char	**dupplicate_grid(t_map *map);
int	flood_fill(char **grid, int x, int y, t_map *map);

//utils map
void	*safe_malloc(t_data *data, size_t size);
int	is_valid_map_line(char *line);
void	count_map_elements(t_data *data, int *player_count, int *empty_spaces);
int is_player_char(char c);

//parsing utils
int is_texture_line(char *line);
int is_color_line(char *line);
char *skip_whitespace(char *line);
int is_empty_line(char *line);
int identify_texture_type(char *line, t_data *data);
char *extract_texture_path(char *line, int texture_type, t_data *data);
void assign_texture_to_data(t_data *data, char *path, int texture_type);
int parse_texture_line(char *line, t_data *data);
int check_config_complete(t_data *data);
char *trim_whitespace(char *str);

//check colors
int parse_rgb_value(char **str);
int encode_rgb_color(int r, int g, int b);
int identify_color_type(char *line, t_data *data);
void assign_rgb_values(t_data *data, int r, int g, int b, int color_type);
void parse_rgb_values(char *color_start, t_data *data, int color_type);
int parse_color_line(char *line, t_data *data);

//player
void	find_player_position(t_data *data, int *x, int *y);

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

void cast_ray(t_ray *ray, double start_x, double start_y, double dir_x, double dir_y, t_data *data);
void	render_scene(t_data *data);
void	init_direction_ns(t_player *player, t_map *map);
void	init_direction_ew(t_player *player, t_map *map);


//check_texture
int check_texture_file(char *path);
void parse_texture(t_data *data, char *line);


#endif