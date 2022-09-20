HEADER = cub3d.h

SRC = 	main.c \
		raycasting/map.c raycasting/rays.c \
		utils/utils.c \
		parser/parser.c parser/check_map.c parser/read_file.c parser/record_info.c parser/parser_utils.c \
		parser/format_map.c
#
OBJ = $(SRC:.c=.o)
#
SRC_BONUS = map.c
#
OBJ_BONUS = $(SRC_BONUS:.c=.o)
#
FLAGS = -Wall -Werror -Wextra
#
LIBFT	= ./libft/libft.a
LIBMLX = ./libmlx/libmlx.a
#
MLX_FLAGS = -framework OpenGL -framework AppKit
MATH_FLAGS = -lm
#
NAME = cub3D
#
all: libft $(NAME)
#
$(NAME): $(OBJ) $(HEADER) Makefile
	@make -C ./libft
	@make -C ./libmlx
	@$(CC) $(FLAGS) $(MATH_FLAGS) $(MLX_FLAGS) $(OBJ) $(LIBFT) $(LIBMLX) -o $@
	@echo "\033[32m\033[40m\033[1m[cub3D compiled]"
#

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@
#
libmlx :
	@make -s -C libmlx

libft :
	@make -s -C libft
#
bonus: $(OBJ_BONUS)
	$(CC) $(CC_FLAGS) $(MATH_FLAGS) $(MLX_FLAGS) $(OBJ_BONUS) -o $(NAME)
#
clean:
	@make -s -C libmlx clean
	@make -s -C libft clean
	@rm -rf $(OBJ) $(OBJ_BONUS)
	@echo "\033[31m\033[40m\033[1m[all clean]"
#
fclean: clean
	@rm -rf $(NAME)
	@$(RM) libft/libft.a
#
re: fclean all
