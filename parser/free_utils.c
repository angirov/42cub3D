/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 22:55:36 by mokatova          #+#    #+#             */
/*   Updated: 2022/12/15 23:00:16 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_colors(t_parser *game, int i)
{
	int	j;

	j = 0;
	while (game->settings->textures[i].colors[j])
		free(game->settings->textures[i].colors[j++]);
	free(game->settings->textures[i].colors);
	game->settings->textures[i].colors = NULL;
}

void	free_settings(t_parser *game)
{
	int	i;

	i = 0;
	if (game->settings)
	{
		while (i < 4)
		{
			if (game->settings->textures[i].ptr)
			{
				free_colors(game, i);
				mlx_destroy_image(game->mlx, game->settings->textures[i].ptr);
			}
			i++;
		}
		free(game->settings);
	}
}
