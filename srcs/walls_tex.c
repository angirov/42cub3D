/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:22:36 by vangirov          #+#    #+#             */
/*   Updated: 2022/12/15 02:06:44 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

enum e_dirs {n, s, e, w};

int	side_dir(t_loc ray_dir, int side)
{
	enum e_dirs	dir;

	if (side == 1)
	{
		if (ray_dir.y >= 0)
			dir = s;
		else
			dir = n;
	}
	else
	{
		if (ray_dir.x >= 0)
			dir = e;
		else
			dir = w;
	}
	return (dir);
}

int	my_set_color(t_loc ray_dir, int side)
{
	enum e_dirs	dir;
	int			color;

	dir = side_dir(ray_dir, side);
	if (dir == n)
		color = RED;
	else if (dir == s)
		color = WHITE;
	else if (dir == e)
		color = YELLOW;
	else if (dir == w)
		color = GRAY;
	return (color);
}

bool	is_wall(t_game *g, int x, int y)
{
	return (ft_strchr("1  ", map_value(g, x, y)));
}
