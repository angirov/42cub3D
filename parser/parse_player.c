/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:34:43 by mokatova          #+#    #+#             */
/*   Updated: 2022/12/16 18:39:17 by vangirov         ###   ########.fr       */
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
	if (c == 'W')
		game->map->player_dir = 0;
	else if (c == 'N')
		game->map->player_dir = 90;
	else if (c == 'E')
		game->map->player_dir = 180;
	else if (c == 'S')
		game->map->player_dir = 270;
}

int	are_surroundings_ok(char **values, int i, int j)
{
	int	i_incr;
	int	i_decr;
	int	j_incr;
	int	j_decr;

	i_incr = i + 1;
	i_decr = i - 1;
	j_incr = j + 1;
	j_decr = j - 1;
	if (is_spot_blank(values[i_decr][j_decr]) == 1
		|| is_spot_blank(values[i_decr][j]) == 1
		|| is_spot_blank(values[i_decr][j_incr]) == 1
		|| is_spot_blank(values[i][j_decr]) == 1
		|| is_spot_blank(values[i][j_incr]) == 1
		|| is_spot_blank(values[i_incr][j_decr]) == 1
		|| is_spot_blank(values[i_incr][j]) == 1
		|| is_spot_blank(values[i_incr][j_incr]) == 1)
		return (1);
	return (0);
}

int	is_spot_blank(char c)
{
	if (c == ' ' || c == '\0')
		return (1);
	return (0);
}

void	free_array(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
	argv = NULL;
}
