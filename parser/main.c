/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 16:57:30 by mokatova          #+#    #+#             */
/*   Updated: 2022/09/30 19:29:22 by mokatova         ###   ########.fr       */
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
	quit_game(&game, 0, NULL);
}
