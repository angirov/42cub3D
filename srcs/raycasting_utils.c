/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 01:53:35 by mokatova          #+#    #+#             */
/*   Updated: 2022/12/15 02:01:36 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

void	calculate_params(t_game *g, t_raycast *rc, int i, int x)
{
	rc->line_height = (int)(g->graphics->screen_height / g->distances_corr[x]);
	rc->draw_start = -rc->line_height / 2
		+ g->graphics->screen_height * HORISONT;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_height / 2 + g->graphics->screen_height * HORISONT;
	if (rc->draw_end >= g->graphics->screen_height)
		rc->draw_end = g->graphics->screen_height - 1;
	if (g->sides[x] == 0)
		g->wallhits = g->player->loc.y + g->distances_corr[x] * g->ray_dirs[x].y;
	else
		g->wallhits = g->player->loc.x + g->distances_corr[x] * g->ray_dirs[x].x;
	g->wallhits -= floor(g->wallhits);
	rc->tex_x = (int)(g->wallhits * g->parser->settings->textures[i].width);
	if (g->sides[x] == 0 && g->ray_dirs[x].x > 0)
		rc->tex_x = g->parser->settings->textures[i].width - rc->tex_x - 1;
	if (g->sides[x] == 1 && g->ray_dirs[x].y < 0)
		rc->tex_x = g->parser->settings->textures[i].width - rc->tex_x - 1;
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
