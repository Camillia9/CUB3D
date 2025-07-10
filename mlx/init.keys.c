#include "../includes/cub3d.h"

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_game(data);
	if (keycode < 256)
		data->keys[keycode] = 1;
	else if(keycode == KEY_LEFT)
		data->arrow_keys[0] = 1;
	else if(keycode == KEY_RIGHT)
		data->arrow_keys[1] = 1;
	return (0);
}

int handle_keyrelease(int keycode, t_data *data)
{
	if (keycode < 256)
		data->keys[keycode] = 0;
	if (keycode == KEY_LEFT)
		data->arrow_keys[0] = 0;
	if (keycode == KEY_RIGHT)
		data->arrow_keys[1] = 0;
	return (0);
}

void	handle_mouvement(t_data *data)
{
	int moves = 0;

	if (data->keys[KEY_W])
	{
		move_forward(data);
		moves = 1;
	}
	if (data->keys[KEY_S])
	{
		move_backward(data);
		moves =1;
	}
	if (data->keys[KEY_A])
	{
		move_left(data);
		moves = 1;
	}
	if (data->keys[KEY_D])
	{
		move_right(data);
		moves =1;
	}
	if (moves)
		render_frame(data);
}

void	handle_mouvement_2(t_data *data)
{
	int moves = 0; 

	if (data->arrow_keys[0])
	{
		rotate_left(data);
		moves = 1;
	}
	if (data->arrow_keys[1])
	{
		rotate_right(data);
		moves = 1;
	}
	if (moves)
		render_frame(data);
}
