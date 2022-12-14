/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:20:19 by vangirov          #+#    #+#             */
/*   Updated: 2022/12/15 01:52:27 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_all(t_game *game)
{
	draw_floor_n_ceiling(game->graphics, game->parser->settings);
	cast_rays(game->player);
	map_background(game);
	draw_grid(game);
	draw_rays(game);
	mlx_put_image_to_window(game->graphics->mlx_ptr, game->graphics->win_ptr,
		game->graphics->img_prt, 0, 0);
}

void	call_parser(t_game *g, int argc, char **argv)
{
	if (argc != 2)
		quit_game(g->parser, WRNG_ARG, NULL);
	g->parser = malloc(sizeof(t_parser));
	*g->parser = (t_parser){0};
	g->parser->mlx = g->graphics->mlx_ptr;
	parse(g->parser, argv[1]);
	set_sizes(g, g->parser->map->columns, g->parser->map->rows, 20);
}

void	inits_for_casting(t_game *game)
{
	int	screen;

	screen = game->graphics->screen_width;
	game->distances_corr = malloc(sizeof(double) * screen);
	game->distances_true = malloc(sizeof(double) * screen);
	game->sides = malloc(sizeof(int) * screen);
	game->ray_dirs = malloc(sizeof(t_loc) * screen);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	game->graphics = api_init_graphics(1600, 800, TITLE);
	inits_for_casting(game);
	call_parser(game, argc, argv);
	game->player = (t_player *)malloc(sizeof(t_player));
	game->player->game = game;
	player_set_locdir(game);
	game->player->speed = 0.2;
	game->player->rotation_radian = dtr(10);
	draw_all(game);
	mlx_hook(game->graphics->win_ptr, 17, 0, ft_destroy, game);
	mlx_key_hook(game->graphics->win_ptr, deal_key, game);
	mlx_loop(game->graphics->mlx_ptr);
	return (0);
}
