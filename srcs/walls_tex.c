/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:22:36 by vangirov          #+#    #+#             */
/*   Updated: 2022/12/10 01:16:47 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

enum dirs {N, S, E, W};

int	side_dir(t_loc ray_dir, int side)
{
	enum dirs dir;
	if (side == 1)
	{
		if (ray_dir.y >= 0)
			dir = S;
		else
			dir = N;
	}
	else
	{
		if (ray_dir.x >= 0)
			dir = E;
		else
			dir = W;
	}
	return dir;
}

int	my_set_color(t_loc ray_dir, int side)
{
	enum dirs	dir;
	int			color;

	dir = side_dir(ray_dir, side);
	if (dir == N)
		color = RED;
	else if (dir == S)
		color = WHITE;
	else if (dir == E)
		color = YELLOW;
	else if (dir == W)
		color = GRAY;
	return (color);
}

// void	wall_hits(t_game *g)
// {
// 	int		screen;
// 	int		x;
// 	double	degrees;
// 	double	wall;

// 	screen = g->graphics->screen_width;
// 	g->wallhits = malloc(sizeof(double) * screen);
// 	x = 0;
// 	while (x < screen)
// 	{
// 		degrees = atan(g->ray_dirs[x].y / g->ray_dirs[x].x);
// 		if (g->sides[x] == 0)
// 			wall = g->player->loc.y + g->distances[x] * cos(degrees);
// 		else
// 			wall = g->player->loc.x + g->distances[x] * sin(degrees);
// 		wall -= (int)wall;
// 		g->wallhits[x] = wall;
// 		x++;
// 	}
// }

// void	draw_walls(t_game *g)
// {
// 	int	screen;
// 	int h;
// 	int lineHeight;
// 	int drawStart;
// 	int drawEnd;
// 	screen = g->graphics->screen_width;
// 	for(int x = 0; x < screen; x++)
// 	{
// 		h = g->graphics->screen_height;
// 		lineHeight = (int)(h / g->distances[x]);
// 		drawStart = -lineHeight / 2 + h * HORISONT;
// 		if(drawStart < 0)
// 			drawStart = 0;
// 		drawEnd = lineHeight / 2 + h * HORISONT;
// 		if(drawEnd >= h)
// 			drawEnd = h - 1;
// 		int color = my_set_color(g->ray_dirs[x], g->sides[x]);
// 		draw_line((t_loc){x, drawStart}, (t_loc){x, drawEnd}, 1, color, g->graphics);
// 	}
// 	wall_hits(g);
// }
