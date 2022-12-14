/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits_linux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:00:36 by vangirov          #+#    #+#             */
/*   Updated: 2022/12/16 00:59:23 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// void	ft_error(t_game *game, char *message)
// {
// 	ft_destroy(game);
// 	perror(message);
// 	exit(1);
// }

// void	ft_escape(t_game *game)
// {
// 	ft_destroy(game);
// 	exit(0);
// }

void	ft_free_game(t_game *game)
{
	free(game->graphics);
	free(game->player);
	free(game->distances_corr);
	free(game->distances_true);
	free(game->sides);
	free(game->ray_dirs);
	free(game);
}

// void	ft_free_mlx_linux(void *mlx_ptr, void *win_ptr, void *img_prt)
// {
// 	mlx_destroy_image(mlx_ptr, img_prt);
// 	mlx_destroy_window(mlx_ptr, win_ptr);
// 	mlx_destroy_display(mlx_ptr);
// }

// void	ft_free_mlx_macos(void *mlx_ptr, void *win_ptr, void *img_prt)
// {
// 	mlx_destroy_image(mlx_ptr, img_prt);
// 	mlx_destroy_window(mlx_ptr, win_ptr);
// }

int	ft_destroy(t_game *game)
{
	if (game->parser->map)
	{
		if (game->parser->map->values)
			free_array(game->parser->map->values);
		free(game->parser->map);
	}
	free_settings(game->parser);
	api_free_graphics(game->graphics->mlx_ptr,
		game->graphics->win_ptr, game->graphics->img_prt);
	free(game->graphics->mlx_ptr);
	ft_free_game(game);
	exit(0);
}
