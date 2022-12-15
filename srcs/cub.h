/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 19:05:05 by vangirov          #+#    #+#             */
/*   Updated: 2022/12/15 19:05:11 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

/* for strerror */
# include <string.h>
# include <errno.h>

/* for perror */
# include <stdio.h> 

# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>

# define _USE_MATH_DEFINES
# define SHIFT_VAL 100
# define ANGLE_DIV 36

// window
# define WIDTH 1600
# define HEIGHT 800
# define HORISONT 0.7
# define TITLE "Cub3D"

// colors
# define WHITE 0xffffff
# define RED 0xe80c0c
# define YELLOW 0xffff00 // e69138
# define GRAY 0x444444
# define L_GRAY 0xbebebe

# include "libft.h"
# include "mlx_api.h"
# include "parser.h"

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_fpoint
{
	float	x;
	float	y;
	float	z;
	int		color;
}	t_fpoint;

typedef struct s_map	t_map;
typedef struct s_game	t_game;
typedef struct s_parser	t_parser;

typedef struct s_loc
{
	double	x;
	double	y;
}	t_loc;

typedef struct s_player
{
	t_game	*game;
	t_loc	loc;
	double	direction;
	double	rotation_radian;
	double	speed;
}	t_player;

typedef struct s_grid
{
	int	heigth;
	int	width;

}	t_grid;

typedef struct s_game
{
	t_graphics	*graphics;
	t_player	*player;
	t_grid		grid;
	t_parser	*parser;
	int			px_width;
	int			px_heigth;
	char		*map;
	int			scale;
	t_loc		*ray_dirs;
	double		*distances_corr;
	double		*distances_true;
	int			*sides;
	double		wallhits;
}	t_game;

typedef struct s_raycast
{
	int		screen;
	t_loc	dir_vec;
	t_loc	plane_vec;
	int		map_x;
	int		map_y;
	t_loc	delta_corr;
	t_loc	delta_true;
	t_loc	side_dist_corr;
	t_loc	side_dist_true;
	int		step_x;
	int		step_y;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	t_color	color;
	int		pix;
}	t_raycast;

void	set_sizes(t_game *game, int width, int heigth, int scale);
void	player_set_locdir(t_game *g);

void	player_move(t_player *player, int dir_grades);
void	player_turn_right(t_player *player);
void	player_turn_left(t_player *player);

// math.c
double	vec_len(t_loc vec);
t_loc	norm_vec(t_loc vec);
t_loc	dir2vec(double radians);
t_loc	add_vecs(t_loc vec1, t_loc vec2);
t_loc	sc_mult(t_loc vec, double scalar);

// math2.c
double	rtd(double radians);
double	dtr(double degrees);
double	ft_abs(double num);
double	ft_max(double a, double b);

// dist_true.c
void	set_step_side_dist_true(t_game *g, t_raycast *rc, int x);
void	set_side_dist_true(t_game *g, t_raycast *rc, int x, int side);

// drawing.c
void	draw_line(t_loc l0, t_loc l1, int color, t_game *g);
void	ft_plot_f_line(t_fpoint p0, t_fpoint p1, int color, t_graphics *g);
void	ft_plot_line(t_point p0, t_point p1, int color, t_graphics *g);
void	fill_sqare(t_game *g, t_loc corner, int side, int color);
void	fill_rect(t_game *g, t_loc corner, int x, int y);

// minimap.c
void	draw_rays(t_game *g);
int		map_value(t_game *g, int x, int y);
void	fill_grid(t_game *g, int x, int y, int scale);
void	map_background(t_game *g);
void	draw_grid(t_game *g);

// raycasting.c
void	cast_rays(t_player	*p);
void	draw_walls(t_game *g);

// raycasting_utils.c
void	draw_floor_n_ceiling(t_graphics *graphics, t_settings *settings);
void	calculate_params(t_game *g, t_raycast *rc, int i, int x);
void	pick_correct_texture(t_game *game, int x, int *i);
void	render_textures(t_game *g, t_raycast *rc, int x);

// key_hooks.c
int		deal_key(int key, t_game *game);

// exit.c 
// void	ft_error(t_game *g, char *message);
int		ft_destroy(t_game *g);

// walls_tex.c
bool	is_wall(t_game *g, int x, int y);
void	ft_put_pixel(t_graphics *graphics, int x, int y, int color);

#endif
