#include "../includes/cub3d.h"

static void	init_ray(t_ray *ray, double start_x, double start_y, double dir_x, double dir_y)
{
    ray->map_x = (int)start_x;
    ray->map_y = (int)start_y;
	ray->dir_x = dir_x;
	ray->dir_y = dir_y;
    ray->hit_wall = 0;
    ray->side = 0;
}

static void	calculate_delta_distance(t_ray *ray)
{
	// Distance pour parcourir une case complète dans chaque direction
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->dir_y);
}

static void	step_and_side(t_ray *ray, double start_x, double start_y)
{	
	if (ray->dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (start_x - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - start_x) * ray->delta_dist_x;
    }
    if (ray->dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (start_y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - start_y) * ray->delta_dist_y;
    }
}

static void	algo_DDA(t_ray *ray)
{
	while (ray->hit_wall == 0)
	{
		// Avancer au prochain côté de grille
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		// Vérifier si on a touché un mur
		if (is_wall(ray->map_x, ray->map_y))
			ray->hit_wall = 1;
	}
}
// Fonction cast_ray corrigée
void cast_ray(t_ray *ray, double start_x, double start_y, double dir_x, double dir_y)
{
	init_ray(ray, start_x, start_y, dir_x, dir_y);
	calculate_delta_distance(ray);
    step_and_side(ray, start_x, start_y);
	algo_DDA(ray);

    if (ray->side == 0)
        ray->distance = (ray->map_x - start_x + (1 - ray->step_x) / 2) / ray->dir_x;
    else
        ray->distance = (ray->map_y - start_y + (1 - ray->step_y) / 2) / ray->dir_y;

		// Protection distance minimal (au cas ou probleme, ici pas fonctionnel)
	//if (ray->distance < 0.01)
    //    ray->distance = 0.01;
	
    ray->wall_x = ray->map_x;
    ray->wall_y = ray->map_y;
}
