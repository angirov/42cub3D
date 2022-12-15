NAME = cub3D

SRCS_DIR = srcs/
SRCS_FILES =	main.c \
				mlx_api/free_mlx.c \
				dist_true.c \
				drawing.c \
				exits_linux.c \
				game.c \
				key_hooks.c \
				math.c \
				minimap.c \
				raycasting.c \
				walls_tex.c \
				raycasting_utils.c \
				math2.c

PARSER_FILES =	parser/colors_n_textures.c \
				parser/errors.c \
				parser/map_checker.c \
				parser/parse.c \
				parser/parse_map_utils.c \
				parser/parse_player.c


SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES)) $(PARSER_FILES)

OBJ = $(SRCS:.c=.o)

HEADERS = $(SRCS_DIR)cub.h

# ========== libraries ==========
LIB_DIR = libs

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

ALL_LIBS = $(LIBFT_A)

MLX_PATH	=	minilibx-linux
MLX_LIB		=	mlx_Linux

# ========== compilation ==========
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wno-unused-parameter
MLX_FLAFS = -L/usr/lib -lXext -lX11 -lm -lz
MODULES = 	mlx_api \
			game
MODULES_DIRS = $(addprefix $(SRCS_DIR), $(MODULES))
MODULES_INCL = $(addprefix -I, $(MODULES_DIRS))
INCLUDES_LOCAL = -I$(SRCS_DIR) -I$(LIBFT_DIR) $(MODULES_INCL) -Iparser

RM = rm -rf

# ========== rules ==========
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(INCLUDES_LOCAL) $(ALL_LIBS) $(HEADERS) -L$(MLX_PATH) -l$(MLX_LIB) $(MLX_FLAFS) -o $(NAME)

%.o: %.c $(HEADERS) makelibs
	$(CC) $(CFLAGS) $(INCLUDES_LOCAL) -I/usr/include -c $< -o $@ 

makelibs:
	make -C $(LIBFT_DIR)
	make -C $(MLX_PATH)

clean: cleanlibs
	$(RM) $(OBJ)

fclean: fcleanlibs
	$(RM) $(OBJ) $(NAME)

cleanlibs:
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_PATH)

fcleanlibs:
	make fclean -C $(LIBFT_DIR)
	make clean -C $(MLX_PATH)

test:
	@echo $(OBJ)

.PHONY: all clean fclean re makelibs test