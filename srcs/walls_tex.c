/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:22:36 by vangirov          #+#    #+#             */
/*   Updated: 2022/12/12 21:30:17 by vangirov         ###   ########.fr       */
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
