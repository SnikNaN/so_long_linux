NAME = so_long
HEADERS_DIRS = includes $(LIBFT_DIR) $(MINILIBX_DIR)
B_HEADERS_DIRS = includes_bonus $(LIBFT_DIR) $(MINILIBX_DIR) cute_png
HEADERS = includes/so_long.h includes/get_next_line.h $(LIBFT_DIR)/libft.h $(MINILIBX_DIR)/mlx.h
B_HEADERS = includes_bonus/so_long_bonus.h includes_bonus/get_next_line_bonus.h $(LIBFT_DIR)/libft.h $(MINILIBX_DIR)/mlx.h cute_png/cute_png.h
CC = gcc
C_FLAGS = -g#-Wall -Wextra -Werror
LIBFT_DIR = libft
MINILIBX_DIR = minilibx-linux
LIBFT = $(LIBFT_DIR)/libft.a
LIB = ft
MINILIBX = $(MINILIBX_DIR)/libmlx.a
SRC_DIR = srcs
OBJ_DIR = obj
B_SRC_DIR = srcs_bonus
SRCS = main	\
		get_next_line \
		get_next_line_utils \
		parse_map \
		load_resources \
		check_rules \
		file_utils \
		fix_minilibx \
		randomizer \
		render_utils
B_SRCS =  main_bonus \
			get_next_line_bonus \
			get_next_line_utils_bonus \
			map_utils_bonus \
			load_resources_bonus \
			load_resources_2_bonus \
			check_rules_bonus \
			file_utils_bonus \
			fix_minilibx_bonus \
			randomizer_bonus \
			render_utils_bonus \
			animations_bonus \
			animations_2_bonus \
			eggs_utils_bonus \
			enemy_logics_bonus \
			free_utils_bonus
OBJ_FILE = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRCS)))
B_OBJ_FILE = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(B_SRCS)))
SRC_FILE = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRCS)))

CUTE_PNG = cute_png/cute_png.o

all: check_libft check_mlx $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(CUTE_PNG) $(OBJ_FILE)
	$(CC) $(C_FLAGS) $(OBJ_FILE) $(CUTE_PNG) -L$(LIBFT_DIR) -lft -L./$(MINILIBX_DIR) -lmlx -lX11 -lXext -lXrender -lXrandr -lm  -o $(NAME)

bonus:
	$(MAKE) OBJ_FILE="$(B_OBJ_FILE)" SRC_DIR="$(B_SRC_DIR)" HEADERS_DIRS="$(B_HEADERS_DIRS)" HEADERS="$(B_HEADERS)" all

check_libft:
	$(MAKE) bonus -C $(LIBFT_DIR)

check_mlx:
	$(MAKE) -C $(MINILIBX_DIR)

$(LIBFT): check_libft

$(MINILIBX): check_mlx

$(CUTE_PNG):
	$(MAKE) -C ./cute_png

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	mkdir -p $(@D)
	$(CC) -c $(C_FLAGS) $(foreach h, $(HEADERS_DIRS), -I$h) $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MINILIBX_DIR)
	rm $(CUTE_PNG)


fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(MINILIBX)

re: fclean all

.PHONY: all, clean, fclean, re, check_libft, check_mlx, bonus