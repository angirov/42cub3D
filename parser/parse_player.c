/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:34:43 by mokatova          #+#    #+#             */
/*   Updated: 2022/10/26 13:42:26 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_player(t_parser *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map->rows)
	{
		j = 0;
		while (j < game->map->columns)
		{
			if (game->map->values[i][j] == 'N'
				|| game->map->values[i][j] == 'S'
				|| game->map->values[i][j] == 'E'
				|| game->map->values[i][j] == 'W')
			{
				game->map->player_x = j;
				game->map->player_y = i;
				assign_direction(game, game->map->values[i][j]);
				return ;
			}
			j++;
		}
		i++;
	}
}

void	assign_direction(t_parser *game, char c)
{
	if (c == 'E')
		game->map->player_dir = 0;
	else if (c == 'N')
		game->map->player_dir = 90;
	else if (c == 'W')
		game->map->player_dir = 180;
	else if (c == 'S')
		game->map->player_dir = 270;
}
