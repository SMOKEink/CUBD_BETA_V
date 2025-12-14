NAME = cub3d

SRC = $(shell find . -name "*.c" -not -path "./.mlx/*")
OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O3

MLX_DIR = .mlx
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz


all : $(NAME)

$(NAME): $(OBJ) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o $@

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) -I. -I$(MLX_DIR) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re mlx
