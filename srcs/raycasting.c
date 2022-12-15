/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 10:32:40 by vangirov          #+#    #+#             */
/*   Updated: 2022/12/15 16:14:05 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	set_ray_dir(t_game *g, t_raycast *rc, int x)
{
	double	camera;
	t_loc	ray_dir;

	camera = 2 * x / (double)rc->screen - 1;
	ray_dir = add_vecs(rc->dir_vec, sc_mult(rc->plane_vec, camera));
	g->ray_dirs[x] = ray_dir;
	rc->delta_true.x = sqrt(1 + (g->ray_dirs[x].y * g->ray_dirs[x].y)
			/ (g->ray_dirs[x].x * g->ray_dirs[x].x));
	rc->delta_true.y = sqrt(1 + (g->ray_dirs[x].x * g->ray_dirs[x].x)
			/ (g->ray_dirs[x].y * g->ray_dirs[x].y));
	if (g->ray_dirs[x].x == 0)
		rc->delta_corr.x = 1e30;
	else
		rc->delta_corr.x = fabs(1 / g->ray_dirs[x].x);
	if (g->ray_dirs[x].y == 0)
		rc->delta_corr.y = 1e30;
	else
		rc->delta_corr.y = fabs(1 / g->ray_dirs[x].y);
}

void	set_step_side_dist_corr(t_game *g, t_raycast *rc, int x)
{
	if (g->ray_dirs[x].x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_corr.x = (g->player->loc.x - rc->map_x)
			* rc->delta_corr.x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_corr.x = (rc->map_x + 1.0 - g->player->loc.x)
			* rc->delta_corr.x;
	}
	if (g->ray_dirs[x].y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_corr.y = (g->player->loc.y - rc->map_y)
			* rc->delta_corr.y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_corr.y = (rc->map_y + 1.0 - g->player->loc.y)
			* rc->delta_corr.y;
	}
}

void	set_side_dist_corr(t_game *g, t_raycast *rc, int x, int side)
{
	if (side == 0)
		rc->side_dist_corr.x = (rc->side_dist_corr.x - rc->delta_corr.x);
	else
		rc->side_dist_corr.y = (rc->side_dist_corr.y - rc->delta_corr.y);
	if (rc->side_dist_corr.x < rc->side_dist_corr.y)
		g->distances_corr[x] = rc->side_dist_corr.x;
	else
		g->distances_corr[x] = rc->side_dist_corr.y;
}

void	perform_rc(t_game *g, t_raycast *rc, int x)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (rc->side_dist_corr.x < rc->side_dist_corr.y)
		{
			rc->side_dist_corr.x += rc->delta_corr.x;
			rc->side_dist_true.x += rc->delta_true.x;
			rc->map_x += rc->step_x;
			g->sides[x] = 0;
		}
		else
		{
			rc->side_dist_corr.y += rc->delta_corr.y;
			rc->side_dist_true.y += rc->delta_true.y;
			rc->map_y += rc->step_y;
			g->sides[x] = 1;
		}
		if (is_wall(g, rc->map_x, rc->map_y))
			hit = 1;
	}
}

void	cast_rays(t_player *p)
{
	t_raycast	rc;
	int			x;

	rc.screen = p->game->graphics->screen_width;
	rc.dir_vec = dir2vec(p->direction);
	rc.plane_vec = dir2vec(p->direction + dtr(90));
	x = 0;
	while (x < rc.screen)
	{
		rc.map_x = (int)p->loc.x;
		rc.map_y = (int)p->loc.y;
		set_ray_dir(p->game, &rc, x);
		set_step_side_dist_corr(p->game, &rc, x);
		set_step_side_dist_true(p->game, &rc, x);
		perform_rc(p->game, &rc, x);
		set_side_dist_corr(p->game, &rc, x, p->game->sides[x]);
		set_side_dist_true(p->game, &rc, x, p->game->sides[x]);
		render_textures(p->game, &rc, x);
		x++;
	}
}
