#include "../includes/cub3d.h"

int close_game(t_data *data)
{
    printf("Game closed\n");
    
    if (data->mlx.img)
        mlx_destroy_image(data->mlx.mlx, data->mlx.img);
    if (data->mlx.win)
        mlx_destroy_window(data->mlx.mlx, data->mlx.win);
    if (data->mlx.mlx)
    {
        mlx_destroy_display(data->mlx.mlx);
        free(data->mlx.mlx);
    }
    exit(0);
}
