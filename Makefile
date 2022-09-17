SRC = 	map.c rays.c
#
OBJ = $(SRC:.c=.o)
#
SRC_BONUS = map.c
#
OBJ_BONUS = $(SRC_BONUS:.c=.o)
#
CC_FLAGS = -Wall -Werror -Wextra
#
LIB = ./libmlx/libmlx.a
MLX_FLAGS = -framework OpenGL -framework AppKit
MATH_FLAGS = -lm
#
NAME = cub3D
#
all: $(NAME)
#
$(NAME): $(OBJ) Makefile
	@make -C ./libmlx
	@$(CC) $(CC_FLAGS) $(MATH_FLAGS) $(MLX_FLAGS) $(OBJ) $(LIB) -o $@
	@echo "\033[32m\033[40m\033[1m[cub3D compiled]"
#

%.o: %.c
	@$(CC) $(CC_FLAGS) -c $<
#
bonus: $(OBJ_BONUS)
	$(CC) $(CC_FLAGS) $(MATH_FLAGS) $(MLX_FLAGS) $(OBJ_BONUS) -o $(NAME)
#
clean:
	@rm -rf $(OBJ) $(OBJ_BONUS)
	@echo "\033[31m\033[40m\033[1m[all clean]"
#
fclean: clean
	@rm -rf $(NAME)
#
re: fclean all
