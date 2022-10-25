/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 16:57:30 by mokatova          #+#    #+#             */
/*   Updated: 2022/10/25 19:07:35 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

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
