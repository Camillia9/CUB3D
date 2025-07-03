#include "../includes/cub3d.h"

/**
 * Affiche la configuration parsée (pour debug)
 */
void print_config_data(t_data *data)
{
    printf("=== CONFIGURATION PARSED ===\n");
    printf("North texture: %s\n", data->textures.north_path);
    printf("South texture: %s\n", data->textures.south_path);
    printf("West texture: %s\n", data->textures.west_path);
    printf("East texture: %s\n", data->textures.east_path);
    printf("Floor color: RGB(%d,%d,%d) [0x%06X]\n", 
           data->colors.floor_r, data->colors.floor_g, data->colors.floor_b,
           data->colors.floor_color);
    printf("Ceiling color: RGB(%d,%d,%d) [0x%06X]\n", 
           data->colors.ceiling_r, data->colors.ceiling_g, data->colors.ceiling_b,
           data->colors.ceiling_color);
    printf("Screen size: %dx%d\n", data->screen_width, data->screen_height);
    printf("============================\n");
}
