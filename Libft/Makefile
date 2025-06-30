NAME	= libft.a
CC		= cc
CFLAGS	= -Wall -Werror -Wextra
SRCS	= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		ft_isprint.c ft_strdup.c ft_strlen.c ft_memset.c ft_bzero.c \
		ft_memcpy.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
		ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
		ft_strncmp.c ft_atoi.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_calloc.c ft_substr.c ft_strjoin.c ft_itoa.c ft_strtrim.c \
		ft_putchar_fd.c ft_striteri.c ft_strmapi.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_lstclear.c \
		ft_strcpy.c ft_strcat.c ft_strndup.c ft_strcmp.c ft_strncpy.c \
		ft_atoll.c 

BONUS_SRCS = ft_lstsize.c ft_lstnew.c ft_lstadd_front.c ft_lstlast.c \
			 ft_lstadd_back.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c

INC		= libft.h
OBJ		= $(SRCS:.c=.o)
OBJ_BONUS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJ) $(OBJ_BONUS)
	ar -rcs $(NAME) $(OBJ) $(OBJ_BONUS)

clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus