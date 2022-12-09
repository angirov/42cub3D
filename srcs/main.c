/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:20:19 by vangirov          #+#    #+#             */
/*   Updated: 2022/12/09 23:53:48 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_all(t_game *game)
{
	cast_rays(game->player);
	//draw_walls(game);
	map_background(game);
	draw_grid(game);
	draw_rays(game);
	mlx_put_image_to_window(game->graphics->mlx_ptr, game->graphics->win_ptr,
		game->graphics->img_prt, 0, 0);
}

void	call_parser(t_game *g, int argc, char **argv)
{
	g->parser = malloc(sizeof(t_parser));
	*g->parser = (t_parser){0};
	if (argc != 2)
		quit_game(g->parser, WRNG_ARG, NULL);
	g->parser->mlx = g->graphics->mlx_ptr;
	parse(g->parser, argv[1]);
	set_sizes(g, g->parser->map->columns, g->parser->map->rows, 20);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	// Init game
	game = (t_game *)malloc(sizeof(t_game));
	game->graphics = api_init_graphics(1600, 800, TITLE);

	call_parser(game, argc, argv);

	// Init player
	game->player = (t_player *)malloc(sizeof(t_player));
	game->player->game = game;
	player_set_locdir(game);
	game->player->speed = 0.355678;
	game->player->rotation_rate = dtr(15);

	draw_all(game);
	// mlx_hook(data->graphics->win_ptr, 17, 0, ft_destroy, data);
	mlx_key_hook(game->graphics->win_ptr, deal_key, game);
	mlx_loop(game->graphics->mlx_ptr);
	return (argc);
}
