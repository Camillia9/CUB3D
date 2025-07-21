NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIE
MLXFLAGS = -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm

SRCS_DIR = ./

SRCS =  $(SRCS_DIR)mlx/init_game.c \
		$(SRCS_DIR)mlx/init_free.c \
		$(SRCS_DIR)mlx/utils_mlx.c \
		$(SRCS_DIR)mlx/init_textures.c \
		$(SRCS_DIR)main.c \
		$(SRCS_DIR)raycasting/cast_ray.c \
		$(SRCS_DIR)raycasting/rayon.c \
		$(SRCS_DIR)raycasting/test.c \
		$(SRCS_DIR)mlx/init_move.c \
		$(SRCS_DIR)mlx/init_rotate.c \
		$(SRCS_DIR)mlx/init.keys.c \
		$(SRCS_DIR)parsing/init_data.c \
		$(SRCS_DIR)parsing/check_file.c \
		$(SRCS_DIR)parsing/free.c \
		$(SRCS_DIR)parsing/read_file.c \
		$(SRCS_DIR)parsing/parse_config.c \
		$(SRCS_DIR)parsing/check_colors.c \
		$(SRCS_DIR)parsing/check_texture.c \
		$(SRCS_DIR)parsing/check_map.c \
		$(SRCS_DIR)parsing/utils_map.c \
		$(SRCS_DIR)parsing/parsing_utils.c \
		$(SRCS_DIR)parsing/player.c \
		$(SRCS_DIR)parsing/debug.c \

OBJS = $(SRCS:.c=.o)

INCLUDES = -I$(LIBFT_DIR) -I$(PRINTF_DIR) -I$(GET_NEXT_LINE_DIR) -I$(MLX_DIR)

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a
GET_NEXT_LINE_DIR = $(LIBFT_DIR)/get_next_line
GET_NEXT_LINE = $(GET_NEXT_LINE_DIR)/libftgetnextline.a
MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx_Linux.a

all: mlx $(LIBFT) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR) bonus

$(GET_NEXT_LINE):
	make -C $(GET_NEXT_LINE_DIR)

mlx:
	make -C $(MLX_DIR)

$(NAME): $(OBJS) $(LIBFT) $(GET_NEXT_LINE) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(GET_NEXT_LINE) $(MLXFLAGS) -o $(NAME)

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(GET_NEXT_LINE_DIR) clean
	make -C $(MLX_DIR) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	make -C $(GET_NEXT_LINE_DIR) fclean
	make -C $(MLX_DIR) clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re mlx