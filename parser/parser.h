/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 16:57:40 by mokatova          #+#    #+#             */
/*   Updated: 2022/11/28 16:57:49 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define WRNG_ARG 1
# define MAP_RULES 2

# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../libft/libft.h"

typedef struct s_image
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		llen;
	int		endian;
	int		width;
	int		height;
}	t_image;

typedef struct s_settings
{
	int		ceiling_color;
	int		floor_color;
	t_image	textures[4];
}	t_settings;

typedef struct s_map
{
	int		rows;
	int		columns;
	char	**values;
	int		player_dir;
	int		player_x;
	int		player_y;
}	t_map;

typedef struct s_parser
{
	void		*mlx;
	t_settings	*settings;
	t_map		*map;
}	t_parser;

/////errors.c
int		quit_game(t_parser *game, int err_number, char *msg);
void	clean_n_free(t_parser *game);
void	free_array(char **argv);
/////parse.c
void	parse(t_parser *game, char *file);
void	colors_n_textures(int fd, t_parser *game, char **line);
void	is_everything_in_place(t_parser *game);
void	parse_map(t_parser *game, int fd, char *line);
/////colors_n_textures.c
void	set_color(char *line, int *color, t_parser *game, int i);
int		are_colors_valid(char **colors, int *rgb);
int		cub_atoi(char *color);
void	set_textures(char *line, t_parser *game, int j, int i);
int		import_textures(char *line, t_image *texture, t_parser *game);
/////parse_map_utils.c
void	calculate_map_size(t_parser *game, int fd, char *line, t_list **list);
void	malloc_map(t_parser *game);
void	assign_values(t_parser *game, t_list *list);
void	is_map_ok(t_parser *game);
void	clear_list(t_list **list);
/////map_checker.c
void	any_wrong_symbols(t_parser *game, char **values);
void	are_borders_in_place(t_parser *game, char **values);
void	are_tricky_borders_in_place(t_parser *game, char **values);
void	any_extra_players(t_parser *game, char **values);
int		is_valid(char c);
/////parse_player.c
void	parse_player(t_parser *game);
void	assign_direction(t_parser *game, char c);
int		are_surroundings_ok(char **values, int i, int j);
int		is_spot_blank(char c);

#endif
