/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:20:19 by vangirov          #+#    #+#             */
/*   Updated: 2022/12/16 18:03:42 by vangirov         ###   ########.fr       */
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

void	inits_for_casting(t_game *game)
{
	int	screen;

	screen = game->graphics->screen_width;
	game->distances_corr = malloc(sizeof(double) * screen);
	game->distances_true = malloc(sizeof(double) * screen);
	game->sides = malloc(sizeof(int) * screen);
	game->ray_dirs = malloc(sizeof(t_loc) * screen);
}

void	api_init_graphics(t_game *game, int width, int height, char *title)
{
	game->graphics = (t_graphics *)malloc(sizeof(t_graphics));
	game->graphics->screen_width = width;
	game->graphics->screen_height = height;
	game->graphics->mlx_ptr = game->parser->mlx;
	game->graphics->win_ptr = mlx_new_window(game->graphics->mlx_ptr,
			width, height, title);
	game->graphics->img_prt = mlx_new_image(game->graphics->mlx_ptr,
			width, height);
	game->graphics->img_addr = mlx_get_data_addr(game->graphics->img_prt,
			&game->graphics->bits_per_pixel, &game->graphics->line_length,
			&game->graphics->endian);
}

int	main(int argc, char **argv)
{
	t_game		*game;
	t_parser	parser;

	if (argc != 2)
		quit_game(NULL, WRNG_ARG, NULL);
	parser = (t_parser){0};
	parser.mlx = mlx_init();
	parse(&parser, argv[1]);
	game = (t_game *)malloc(sizeof(t_game));
	game->parser = &parser;
	api_init_graphics(game, WIDTH, HEIGHT, TITLE);
	inits_for_casting(game);
	set_sizes(game, game->parser->map->columns, game->parser->map->rows, 20);
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
