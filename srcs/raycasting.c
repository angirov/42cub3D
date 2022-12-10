/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 10:32:40 by vangirov          #+#    #+#             */
/*   Updated: 2022/12/11 02:39:36 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

typedef struct s_raycast
{
	int		screen;
	t_loc	dir_vec;
	t_loc	plane_vec;
	int		map_x;
	int		map_y;
	t_loc	delta;
	t_loc	side_dist;
	int		step_x;
	int		step_y;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	t_color	color;
	int		pix;
}	t_raycast;

void	set_ray_dir(t_game *g, t_raycast *rc, int x)
{
	double	camera;
	t_loc	ray_dir;

	camera = 2 * x / (double)rc->screen - 1;
	ray_dir = add_vecs(rc->dir_vec, sc_mult(rc->plane_vec, camera));
	g->ray_dirs[x] = ray_dir;
	// rc->delta.x = sqrt(1 + (g->ray_dirs[x].y * g->ray_dirs[x].y) / (g->ray_dirs[x].x * g->ray_dirs[x].x));
	// rc->delta.y = sqrt(1 + (g->ray_dirs[x].x * g->ray_dirs[x].x) / (g->ray_dirs[x].y * g->ray_dirs[x].y));
	if (g->ray_dirs[x].x == 0)
		rc->delta.x = 1e30;
	else
		rc->delta.x = fabs(1 / g->ray_dirs[x].x);
	if (g->ray_dirs[x].y == 0)
		rc->delta.y = 1e30;
	else
		rc->delta.y = fabs(1 / g->ray_dirs[x].y);
}

void	set_step_side_dist(t_game *g, t_raycast *rc, int x)
{
	int	map_x;
	int	map_y;

	map_x = rc->map_x;
	map_y = rc->map_y;
	if (g->ray_dirs[x].x < 0)
	{
		rc->step_x = -1;
		rc->side_dist.x = (g->player->loc.x - map_x) * rc->delta.x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist.x = (map_x + 1.0 - g->player->loc.x) * rc->delta.x;
	}
	if (g->ray_dirs[x].y < 0)
	{
		rc->step_y = -1;
		rc->side_dist.y = (g->player->loc.y - map_y) * rc->delta.y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist.y = (map_y + 1.0 - g->player->loc.y) * rc->delta.y;
	}
}

void	set_side_dist(t_game *g, t_raycast *rc, int x, int side)
{
	if (side == 0)
		rc->side_dist.x = (rc->side_dist.x - rc->delta.x);
	else
		rc->side_dist.y = (rc->side_dist.y - rc->delta.y);
	if (rc->side_dist.x < rc->side_dist.y)
		g->distances[x] = rc->side_dist.x;
	else
		g->distances[x] = rc->side_dist.y;
}

void	perform_rc(t_game *g, t_raycast *rc, int x)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (rc->side_dist.x < rc->side_dist.y)
		{
			rc->side_dist.x += rc->delta.x;
			rc->map_x += rc->step_x;
			g->sides[x] = 0;
		}
		else
		{
			rc->side_dist.y += rc->delta.y;
			rc->map_y += rc->step_y;
			g->sides[x] = 1;
		}
		if (is_wall(g, rc->map_x, rc->map_y))
			hit = 1;
	}
}

void	pick_correct_texture(t_game *game, int x, int *i)
{
	if (game->sides[x] == 0 && game->ray_dirs[x].x > 0)
		*i = 3;
	else if (game->sides[x] == 0)
		*i = 2;
	else if (game->sides[x] == 1 && game->ray_dirs[x].y > 0)
		*i = 1;
	else
		*i = 0;
}

void	calculate_params(t_game *g, t_raycast *rc, int i, int x)
{
	rc->line_height = (int)(g->graphics->screen_height / g->distances[x]);
	rc->draw_start = -rc->line_height / 2
		+ g->graphics->screen_height * HORISONT;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_height / 2 + g->graphics->screen_height * HORISONT;
	if (rc->draw_end >= g->graphics->screen_height)
		rc->draw_end = g->graphics->screen_height - 1;
	if (g->sides[x] == 0)
		g->wallhits = g->player->loc.y + g->distances[x] * g->ray_dirs[x].y;
	else
		g->wallhits = g->player->loc.x + g->distances[x] * g->ray_dirs[x].x;
	g->wallhits -= floor(g->wallhits);
	rc->tex_x = (int)(g->wallhits * g->parser->settings->textures[i].width);
	if (g->sides[x] == 0 && g->ray_dirs[x].x > 0)
		rc->tex_x = g->parser->settings->textures[i].width - rc->tex_x - 1;
	if (g->sides[x] == 1 && g->ray_dirs[x].y < 0)
		rc->tex_x = g->parser->settings->textures[i].width - rc->tex_x - 1;
}

void	render_textures(t_game *g, t_raycast *rc, int x)
{
	int		i;
	int		y;
	double	step;
	double	tex_pos;

	pick_correct_texture(g, x, &i);
	calculate_params(g, rc, i, x);
	step = 1.0 * g->parser->settings->textures[i].height / rc->line_height;
	tex_pos = (rc->draw_start - g->graphics->screen_height
			* HORISONT + rc->line_height / 2) * step;
	y = rc->draw_start;
	while (y < rc->draw_end)
	{
		tex_pos += step;
		if (tex_pos - 1 < 0)
			tex_pos = 1;
		else if (tex_pos - 1 > g->parser->settings->textures[i].height)
			tex_pos = g->parser->settings->textures[i].height - 1;
		rc->color = *g->parser->settings->textures[i]
			.colors[rc->tex_x][(int)(tex_pos) - 1];
		rc->pix = (rc->color.a << 24) + (rc->color.r << 16)
			+ (rc->color.g << 8) + (rc->color.b);
		api_put_pixel(g->graphics, x, y, rc->pix);
		y++;
	}
}

void	draw_floor_n_ceiling(t_graphics *graphics, t_settings *settings)
{
	int	y;
	int	t;

	y = -1;
	while (++y < graphics->screen_height - graphics->screen_height * HORISONT)
	{
		t = -1;
		while (++t < graphics->screen_width)
		{
			api_put_pixel(graphics, t, graphics->screen_height - y - 1,
				settings->floor_color);
		}
	}
	while (++y < graphics->screen_height)
	{
		t = -1;
		while (++t < graphics->screen_width)
		{
			api_put_pixel(graphics, t, graphics->screen_height - y - 1,
				settings->ceiling_color);
		}
	}
}

void	cast_rays(t_player *p)
{
	t_raycast	rc;
	int			x;

	rc.screen = p->game->graphics->screen_width;
	rc.dir_vec = dir2vec(p->direction);
	rc.plane_vec = dir2vec(p->direction + dtr(90));
	p->game->distances = malloc(sizeof(double) * rc.screen);
	p->game->sides = malloc(sizeof(int) * rc.screen);
	p->game->ray_dirs = malloc(sizeof(t_loc) * rc.screen);
	x = 0;
	draw_floor_n_ceiling(p->game->graphics, p->game->parser->settings);
	while (x < rc.screen)
	{
		rc.map_x = (int)p->loc.x;
		rc.map_y = (int)p->loc.y;
		set_ray_dir(p->game, &rc, x);
		set_step_side_dist(p->game, &rc, x);
		perform_rc(p->game, &rc, x);
		set_side_dist(p->game, &rc, x, p->game->sides[x]);
		render_textures(p->game, &rc, x);
		x++;
	}
}

// void	init_raycasting(t_player *p, t_raycast *rc)
// {
// 	rc->screen = p->game->graphics->screen_width;	//px
// 	rc->dir_vec = dir2vec(p->direction);
// 	rc->plane_vec = dir2vec(p->direction + dtr(90));
// 	p->game->distances = malloc(sizeof(double) * rc->screen);
// 	p->game->sides = malloc(sizeof(int) * rc->screen);
// 	p->game->ray_dirs = malloc(sizeof(t_loc) * rc->screen);
// 	rc->map_x = (int)p->loc.x;
// 	rc->map_y = (int)p->loc.y;
// }
