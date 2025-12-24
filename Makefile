NAME = cub3d
NAME_BONUS = cub3d_bonus

HED = mandatory/inc/cub3d.h
HED_BONUS = bonus/inc/cub3d_bonus.h

SRC = mandatory/src/parser/check_color_data.c \
mandatory/src/parser/check_outofbounds_floor.c \
mandatory/src/parser/extract_data.c \
mandatory/src/parser/extract_map.c \
mandatory/src/parser/fill_map_space.c \
mandatory/src/parser/ifc_helpers.c \
mandatory/src/parser/interpret_file_content.c \
mandatory/src/parser/merge_data.c \
mandatory/src/parser/parseutils1.c \
mandatory/src/parser/test_assets.c \
mandatory/src/parser/check_duplicates.c \
mandatory/src/parser/check_enclosed.c \
mandatory/src/parser/parse_map_file.c \
mandatory/src/parser/join_file_lines_helper.c \
mandatory/src/parser/check_enclosed_helper.c \
mandatory/src/parser/get_player_pos.c \
mandatory/src/rendering/movements.c \
mandatory/src/rendering/draw_textures.c \
mandatory/src/rendering/movements2.c \
mandatory/src/rendering/rendering.c \
mandatory/src/rendering/start_game.c \
mandatory/src/rendering/load_textures.c \
mandatory/src/rendering/destroy.c \
mandatory/src/rendering/cub3d.c \
mandatory/src/rendering/hooks.c \
mandatory/src/main.c \
mandatory/src/get_next_line/get_next_line.c \
mandatory/src/get_next_line/get_next_line_utils.c \
mandatory/uti/ft_split.c \
mandatory/uti/garbage_collector.c \
mandatory/uti/memory_cleanup.c \
mandatory/uti/strutils0.c \
mandatory/uti/strutils1.c \
mandatory/uti/strutils2.c

SRC_BONUS = bonus/src/bonus/minimap.c \
bonus/src/bonus/door.c \
bonus/src/bonus/hands_sprites.c \
bonus/src/get_next_line/get_next_line_bonus.c \
bonus/src/get_next_line/get_next_line_utils_bonus.c \
bonus/src/parser/join_file_lines_helper_bonus.c \
bonus/src/parser/get_player_pos_bonus.c \
bonus/src/parser/parse_map_file_bonus.c \
bonus/src/parser/check_duplicates_bonus.c \
bonus/src/parser/check_enclosed_helper_bonus.c \
bonus/src/parser/check_enclosed_bonus.c \
bonus/src/parser/check_color_data_bonus.c \
bonus/src/parser/check_outofbounds_floor_bonus.c \
bonus/src/parser/extract_data_bonus.c \
bonus/src/parser/extract_map_bonus.c \
bonus/src/parser/fill_map_space_bonus.c \
bonus/src/parser/ifc_helpers_bonus.c \
bonus/src/parser/interpret_file_content_bonus.c \
bonus/src/parser/merge_data_bonus.c \
bonus/src/parser/parseutils1_bonus.c \
bonus/src/parser/test_assets_bonus.c \
bonus/src/rendering/draw_textures_bonus.c \
bonus/src/rendering/movements2_bonus.c \
bonus/src/rendering/rendering_bonus.c \
bonus/src/rendering/start_game_bonus.c \
bonus/src/rendering/destroy_bonus.c \
bonus/src/rendering/load_textures_bonus.c \
bonus/src/rendering/cub3d_bonus.c \
bonus/src/rendering/hooks_bonus.c \
bonus/src/rendering/movements_bonus.c \
bonus/src/main_bonus.c \
bonus/uti/ft_split_bonus.c \
bonus/uti/garbage_collector_bonus.c \
bonus/uti/memory_cleanup_bonus.c \
bonus/uti/strutils0_bonus.c \
bonus/uti/strutils1_bonus.c \
bonus/uti/strutils2_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O3

MLX_DIR = .mlx
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz


all: $(NAME)

bonus: $(NAME_BONUS)

$(MLX_LIB):
	make -C $(MLX_DIR)

$(NAME): $(OBJ) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o $@

%.o: %.c $(HED)
	$(CC) $(CFLAGS) -I./mandatory/inc/ -I$(MLX_DIR) -c $< -o $@

$(NAME_BONUS) : $(OBJ_BONUS) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(MLX_FLAGS) -o $@

%_bonus.o: %_bonus.c $(HED_BONUS)
	$(CC) $(CFLAGS) -I./bonus/inc/ -I$(MLX_DIR) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_BONUS)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY : all clean fclean re
