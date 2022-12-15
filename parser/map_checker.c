/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:14:33 by mokatova          #+#    #+#             */
/*   Updated: 2022/12/15 22:30:25 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	any_wrong_symbols(t_parser *game, char **values)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (values[i])
	{
		j = 0;
		while (values[i][j])
		{
			if (values[i][j] != '1' && values[i][j] != '0'
				&& values[i][j] != ' ' && values[i][j] != 'N'
				&& values[i][j] != 'S' && values[i][j] != 'E'
				&& values[i][j] != 'W' && values[i][j] != '\n'
				&& values[i][j] != '\0')
				quit_game(game, MAP_RULES,
					"Make sure the map consists of symbols that are allowed");
			j++;
		}
		i++;
	}
}

void	are_borders_in_place(t_parser *game, char **values)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map->rows)
	{
		j = 0;
		while (values[i][j] == ' ')
			j++;
		if ((values[i][j] != '1' && values[i][j] != '\0')
			|| (values[i][ft_strlen(values[i]) - 1] != '1'
				&& values[i][ft_strlen(values[i]) - 1] != '\n'
				&& values[i][ft_strlen(values[i]) - 1] != '\0'))
			quit_game(game, MAP_RULES, "There's a problem with map borders");
	}
	j = 0;
	while (j < game->map->columns && values[0][j]
		&& values[game->map->rows - 1][j])
	{
		if (is_valid(values[0][j]) == -1)
			quit_game(game, MAP_RULES, "There's a problem with map borders");
		else if (is_valid(values[game->map->rows - 1][j]) == -1)
			quit_game(game, MAP_RULES, "There's a problem with map borders");
		j++;
	}
}

void	are_tricky_borders_in_place(t_parser *game, char **values)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map->rows)
	{
		j = 0;
		while (j < game->map->columns)
		{
			if (values[i][j] == '0' || values[i][j] == 'N'
				|| values[i][j] == 'W' || values[i][j] == 'S'
				|| values[i][j] == 'E')
				if (are_surroundings_ok(values, i, j) == 1)
					quit_game(game, MAP_RULES,
						"There's a problem with map borders");
			j++;
		}
		i++;
	}
}

void	any_extra_players(t_parser *game, char **values)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	while (values[i])
	{
		j = 0;
		while (values[i][j])
		{
			if (values[i][j] == 'N' || values[i][j] == 'S'
				|| values[i][j] == 'E' || values[i][j] == 'W')
				player++;
			j++;
		}
		i++;
	}
	if (player != 1)
		quit_game(game, MAP_RULES,
			"Make sure there's only 1 player on the map");
}

int	is_valid(char c)
{
	if (c != '1' && c != ' ' && c != '\n' && c != '\0')
		return (-1);
	return (0);
}
