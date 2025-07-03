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
		$(SRCS_DIR)parsing/check_file.c \



OBJS = $(SRCS:.c=.o)

INCLUDES = -I$(LIBFT_DIR) -I$(PRINTF_DIR) -I$(GET_NEXT_LINE_DIR) -I$(MLX_DIR)

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx_Linux.a

all: mlx $(LIBFT) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

mlx:
	make -C $(MLX_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLXFLAGS) -o $(NAME)

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_DIR) clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re mlx