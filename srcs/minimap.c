/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 10:31:21 by vangirov          #+#    #+#             */
/*   Updated: 2022/12/21 00:04:05 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_rays(t_game *g)
{
	t_loc	hit_point;
	int		screen;
	int		x;

	screen = g->graphics->screen_width;
	x = 0;
	while (x < screen)
	{
		hit_point = sc_mult(norm_vec(g->ray_dirs[x]), g->distances_true[x]);
		draw_line(g->player->loc, add_vecs(g->player->loc, hit_point),
			YELLOW, g);
		x += screen / 100;
	}
}

int	map_value(t_game *g, int x, int y)
{
	return (g->parser->map->values[y][x]);
}

void	fill_grid(t_game *g, int x, int y, int scale)
{
	if (is_wall(g, x, y))
		fill_sqare(g, (t_loc){x, y}, g->scale, GRAY);
}

void	map_background(t_game *g)
{
	fill_rect(g, (t_loc){0, 0}, \
	g->parser->map->rows, g->parser->map->columns);
}

void	draw_grid(t_game *g)
{
	int	x;
	int	y;
	int	s;

	s = g->scale;
	y = 0;
	while (y < g->parser->map->rows)
	{
		x = 0;
		while (x < g->parser->map->columns)
		{
			if (x < g->parser->map->columns)
			{
				draw_line((t_loc){x, y}, (t_loc){x + 1, y},
					GRAY, g);
			}
			if (y <= g->parser->map->rows)
				draw_line((t_loc){x, y}, (t_loc){x, y + 1},
					GRAY, g);
			fill_grid(g, x, y, s);
			x++;
		}
		y++;
	}
}
