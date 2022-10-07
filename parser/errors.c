/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:06:56 by mokatova          #+#    #+#             */
/*   Updated: 2022/09/30 18:58:52 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	quit_game(t_parser *game, int err_number, char *msg)
{
	if (err_number)
	{
		ft_putendl_fd("Error", 2);
		if (err_number == WRNG_ARG)
			ft_putendl_fd("Please, make sure there's one argument - *.cub", 2);
		else if (err_number == MAP_RULES)
			ft_putendl_fd("Please, make sure the map follows the rules", 2);
		else
			ft_putendl_fd(strerror(err_number), 2);
		if (msg)
			ft_putendl_fd(msg, 2);
	}
	if (game)
		clean_n_free(game);
	exit(err_number);
}

void	clean_n_free(t_parser *game)
{
	int	i;

	if (game->map)
	{
		if (game->map->values)
			free_array(game->map->values);
		free(game->map);
	}
	i = 0;
	if (game->settings)
	{
		while (i < 4)
		{
			if (game->settings->textures[i].ptr)
				mlx_destroy_image(game->mlx, game->settings->textures[i].ptr);
			i++;
		}
		free(game->settings);
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
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
