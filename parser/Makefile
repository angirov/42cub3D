
NAME				:=	cub3D
LIBFT_TOOLS_LIB		:=	libft.a
LIBFT_TOOLS_PATH	:=	../libft

LIB_PATH			:=	./
MLX_PATH			:=	../minilibx-linux
MLX_LIB				:=	mlx_Linux

OBJ_FOLDER			:=	objs

HEADERFILE			:=	parser.h

SRC_LIB				:=	

SRCS			:=	parse.c errors.c colors_n_textures.c main.c map_checker.c parse_map_utils.c

OBJS			:=	$(SRCS:%.c=$(OBJ_FOLDER)/%.o)

CFLAGS		:=	-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(MLX_PATH)
	make -C $(LIBFT_TOOLS_PATH)
	$(CC) $(CFLAGS) -g $(OBJS) -L$(LIBFT_TOOLS_PATH) ../libft/libft.a -L$(MLX_PATH) -l$(MLX_LIB) -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

$(OBJS): $(OBJ_FOLDER)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -fr $(OBJ_FOLDER)
	make -C $(MLX_PATH) clean
	make -C $(LIBFT_TOOLS_PATH) clean

fclean: clean
	rm -fr $(NAME)
	make -C $(LIBFT_TOOLS_PATH) fclean

re: fclean all
	make -C $(LIBFT_TOOLS_PATH) re

.PHONY: clean fclean re
