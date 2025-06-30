#ifndef CUB3D_H
# define CUB3D_H

#include "../Libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include "structures.h"
#include "mlx.h"

//MLX
int	init_mlx(t_data *data);
int	handle_keypress(int keycode, t_data *data);
int game_loop(t_data *data);

//Free
int close_game(t_data *data);

#endif