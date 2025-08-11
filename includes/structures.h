#ifndef STRUCTURES_H
# define STRUCTURES_H

enum		e_texture_index
{
	NORTH = 1,
	SOUTH = 2,
	EAST = 3,
	WEST = 4
};

// Strcutures
typedef struct s_map
{
	char **grid;     // Tableau 2D de la carte
	int width;       // Largeur maximale
	int height;      // Nombre de lignes
	int player_x;    // Position X initiale du joueur
	int player_y;    // Position Y initiale du joueur
	char player_dir; // Direction initiale ('N', 'S', 'E', 'W')
}			t_map;


typedef struct s_draw_range
{
	int		start;
	int		end;
}			t_draw_range;

typedef struct s_player
{
	double x;          // Position X dans le monde (coordonnées réelles)
	double y;          // Position Y dans le monde
	double dir_x;      // Vecteur direction X (cos de l'angle)
	double dir_y;      // Vecteur direction Y (sin de l'angle)
	double plane_x;    // Plan de projection X (pour le FOV)
	double plane_y;    // Plan de projection Y
	double move_speed; // Vitesse de déplacement
	double rot_speed;  // Vitesse de rotation
}			t_player;

typedef struct s_texture // 1 texture
{
	void *img;       // Pointeur image MinilibX
	char *data;      // Données pixels de l'image
	int width;       // Largeur en pixels
	int height;      // Hauteur en pixels
	int bpp;         // Bits per pixel
	int line_length; // Longueur d'une ligne en bytes
	int endian;      // Ordre des bytes
	char *path;      // Chemin du fichier (pour debug)
}			t_texture;

typedef struct s_textures // plusieurs textures
{
	t_texture north;  // Texture mur nord
	t_texture south;  // Texture mur sud
	t_texture east;   // Texture mur est
	t_texture west;   // Texture mur ouest
	char *north_path; // Chemin texture nord (du parsing)
	char *south_path; // Chemin texture sud
	char *east_path;  // Chemin texture est
	char *west_path;  // Chemin texture ouest
}			t_textures;

typedef struct s_colors
{
	int floor_r;       // Rouge du sol (0-255)
	int floor_g;       // Vert du sol
	int floor_b;       // Bleu du sol
	int ceiling_r;     // Rouge du plafond
	int ceiling_b;     // Bleu du plafond
	int ceiling_g;     // Vert du plafond
	int floor_color;   // Couleur sol encodée (RGB → int)
	int ceiling_color; // Couleur plafond encodée
}			t_colors;

typedef struct s_mlx
{
	void *mlx;       // Pointeur MLX
	void *win;       // Pointeur fenêtre
	void *img;       // Image de rendu
	char *img_data;  // Données de l'image
	int img_width;   // Largeur image
	int img_height;  // Hauteur image
	int bpp;         // Bits per pixel
	int line_length; // Longueur ligne
	int endian;      // Endian
}			t_mlx;

typedef struct s_ray
{
	double camera_x; // Position X sur l'écran (-1 à 1)
	double dir_x;    // Direction X du rayon
	double dir_y;    // Direction Y du rayon
	
	int map_x; // Case X actuelle
	int map_y; // Case Y actuelle
	
	double delta_dist_x; // Distance pour traverser une case X
	double delta_dist_y; // Distance pour traverser une case Y
	double side_dist_x;  // Distance au prochain bord X
	double side_dist_y;  // Distance au prochain bord Y
	
	int step_x; // Direction du pas X (-1 ou 1)
	int step_y; // Direction du pas Y (-1 ou 1)
	
	int hit_wall;          // 1 si mur touché
	int side;              // Côté touché (0=NS, 1=EW)
	double perp_wall_dist; // Distance perpendiculaire au mur
	
	int line_height; // Hauteur ligne à dessiner
	int draw_start;  // Début Y de la ligne
	int draw_end;    // Fin Y de la ligne
	
	double distance; // Position exacte sur le mur
	int wall_x;      // Position du mur touché
	int wall_y;      // Position du mur touché
	int tex_x;       // Coordonnée X texture
	int tex_num;     // Numéro de texture (0=NO, 1=SO, 2=WE, 3=EA)
}			t_ray;

typedef struct s_ray_params
{
	double	start_x;
	double	start_y;
	double	dir_x;
	double	dir_y;
}			t_ray_params;

typedef struct s_data
{
	char	**file_content;
	t_map map;           // Données de la carte
	t_player player;     // Données du joueur
	t_textures textures; // Toutes les textures
	t_colors colors;     // Couleurs sol/plafond
	t_mlx mlx;           // Données MinilibX
	t_ray ray;           // Structure pour calculs ray-casting

	int screen_width;  // Largeur écran
	int screen_height; // Hauteur écran

	// Flags pour la gestion
	int keys[256];      // État des touches
	int arrow_keys[10]; // Etat des fleches
	int running;        // 1 si le jeu tourne
}			t_data;

#endif