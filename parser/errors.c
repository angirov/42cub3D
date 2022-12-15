/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:06:56 by mokatova          #+#    #+#             */
/*   Updated: 2022/12/16 00:48:28 by mokatova         ###   ########.fr       */
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

#if __linux__

void	clean_n_free(t_parser *game)
{
	if (game->map)
	{
		if (game->map->values)
			free_array(game->map->values);
		free(game->map);
	}
	free_settings(game);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

#else

void	clean_n_free(t_parser *game)
{
	if (game->map)
	{
		if (game->map->values)
			free_array(game->map->values);
		free(game->map);
	}
	free_settings(game);
	if (game->mlx)
	{
		free(game->mlx);
	}
}

#endif

t_color	*save_pxl_color(t_image *texture, int j, int i)
{
	int	*color;

	color = (int *)(texture->addr
			+ (i * texture->llen + j * (texture->bpp / 8)));
	return ((t_color *)color);
}

t_color	***create_array_of_colors(t_image *texture)
{
	t_color	***array;
	int		i;
	int		j;

	array = malloc(sizeof(t_color **) * (texture->height + 1));
	j = 0;
	while (j < texture->height)
	{
		array[j] = malloc(sizeof(t_color *) * (texture->width + 1));
		i = 0;
		while (i < texture->width)
		{
			array[j][i] = save_pxl_color(texture, j, i);
			i++;
		}
		j++;
	}
	array[j] = NULL;
	return (array);
}
