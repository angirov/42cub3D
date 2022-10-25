/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:20:19 by vangirov          #+#    #+#             */
/*   Updated: 2022/10/25 19:21:28 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_all(t_game *game)
{
	cast_rays(game->player);
	draw_walls(game);
	map_background(game);
	draw_grid(game);
	draw_rays(game);
	mlx_put_image_to_window(game->graphics->mlx_ptr, game->graphics->win_ptr,
		game->graphics->img_prt, 0, 0);
}

void	parser(t_game *g, int argc, char **argv)
{
	g->parser = malloc(sizeof(t_parser));
	if (argc != 2)
		quit_game(g->parser, WRNG_ARG, "too few arguments\n");
	*g->parser = (t_parser){0};
	g->parser->mlx = g->graphics->mlx_ptr;
	parse(g->parser, argv[1]);
	// quit_game(g->parser, errno);
}

// void	print_values(t_map *map)
// {
// 	for (int r = 0; r < map->rows; r++)
// 	{
// 		for (int c = 0; r < map->columns; c++)
// 			printf("%c ", map->values[r][c]);
// 		printf("\n");
// 	}
// }
// void    print_values(t_map *map)
// {
//     printf("Rows: %d\n", map->rows);
//     printf("Rows: %d\n", map->columns);
//     for (int r = 0; r < map->rows; r++)
//     {
//         // printf("Row %d: \n", r);
//         for (int c = 0; c < map->columns; c++)
//         {
//             char val = map->values[r][c];
//             if (val != '0' && val != '1' && val != 'N')
//                 printf("%2d ", (int)val);
//             else
//                 printf(" * ");
            
//         }
//         printf("$\n");
//     }
// }
// int	main(int argc, char **argv)
// {
// 	t_game	*game;

// 	// Init game
// 	game = (t_game *)malloc(sizeof(t_game));
// 	game->graphics = api_init_graphics(1600, 800, TITLE);
// 	game->scale = 20;
	
// 	parser(game, argc, argv);
	
// 	// Init player
// 	game->player = (t_player *)malloc(sizeof(t_player));
// 	game->player->game = game;
// 	player_set_location(game->player, (t_loc){1.593465, 2.772435});
// 	game->player->speed = 0.355678;
// 	game->player->direction = dtr(-45 - 180);
// 	game->player->rotation_rate = dtr(15);
// 	print_values(game->parser->map);
// 	//======================================================================================
// 	// void	*img;
// 	// int		img_width;
// 	// int		img_height;
// 	// img = mlx_png_file_to_image(game->graphics->mlx_ptr, "brick.xpm", &img_width, &img_height);
// 	// printf(">>>>>>>>>>>>>>>> %p: img_width %d img_height %d\n", img, img_width, img_height);
// 	//======================================================================================

// 	// draw_all(game);
// 	// mlx_hook(data->graphics->win_ptr, 17, 0, ft_destroy, data);
// 	mlx_key_hook(game->graphics->win_ptr, deal_key, game);
// 	mlx_loop(game->graphics->mlx_ptr);
// 	return (argc);
// }

int	main(int argc, char **argv)
{
	t_parser	game;

	game = (t_parser){0};
	if (argc != 2)
		quit_game(&game, WRNG_ARG, NULL);
	game.mlx = mlx_init();
	parse(&game, argv[1]);
	for (int i = 0; i < game.map->rows; i++) {
		for (int j = 0; j < game.map->columns; j++) {
			ft_putchar_fd(game.map->values[i][j], 1);
		}
		ft_putchar_fd('\n', 1);
	}
	quit_game(&game, 0, NULL);
}
