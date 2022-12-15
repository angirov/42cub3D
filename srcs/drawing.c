/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 10:23:34 by vangirov          #+#    #+#             */
/*   Updated: 2022/12/15 19:04:49 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// Here all rastarization functions are collected

void	draw_line(t_loc l0, t_loc l1, int color, t_game *g)
{
	t_point	pt_px0;
	t_point	pt_px1;

	pt_px0.x = l0.x * g->scale;
	pt_px0.y = l0.y * g->scale;
	pt_px0.color = color;
	pt_px1.x = l1.x * g->scale;
	pt_px1.y = l1.y * g->scale;
	pt_px1.color = color;
	ft_plot_line(pt_px0, pt_px1, color, g->graphics);
}

void	ft_plot_f_line(t_fpoint p0, t_fpoint p1, int color, t_graphics *g)
{
	float	dx;
	float	dy;
	float	max;

	dx = p1.x - p0.x;
	dy = p1.y - p0.y;
	max = ft_max(ft_abs(dx), ft_abs(dy));
	dx /= max;
	dy /= max;
	while ((int)(p0.x - p1.x) || (int)(p0.y - p1.y))
	{
		ft_put_pixel(g, p0.x, p0.y, color);
		p0.x += dx;
		p0.y += dy;
	}
}

void	ft_plot_line(t_point p0, t_point p1, int color, t_graphics *g)
{
	t_fpoint	fpoint0;
	t_fpoint	fpoint1;

	fpoint0.x = p0.x;
	fpoint1.x = p1.x;
	fpoint0.y = p0.y;
	fpoint1.y = p1.y;
	fpoint0.color = p0.color;
	fpoint1.color = p1.color;
	ft_plot_f_line(fpoint0, fpoint1, color, g);
}

void	fill_sqare(t_game *g, t_loc corner, int side, int color)
{
	int	corner_x;
	int	corner_y;
	int	i;
	int	j;

	corner_x = corner.x * g->scale;
	corner_y = corner.y * g->scale;
	i = 0;
	while (i < side * g->scale)
	{
		j = 0;
		while (j < side * g->scale)
		{
			api_put_pixel(g->graphics, corner_x + i, corner_y + j, color);
			j++;
		}
		i++;
	}
}

void	fill_rect(t_game *g, t_loc corner, int x, int y)
{
	int	corner_x;
	int	corner_y;
	int	i;
	int	j;

	corner_x = corner.x * g->scale;
	corner_y = corner.y * g->scale;
	i = 0;
	while (i < y * g->scale)
	{
		j = 0;
		while (j < x * g->scale)
		{
			api_put_pixel(g->graphics, corner_x + i, corner_y + j, L_GRAY);
			j++;
		}
		i++;
	}
}
