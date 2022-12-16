/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:57:53 by vangirov          #+#    #+#             */
/*   Updated: 2022/12/16 22:11:52 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_clear_image(t_graphics *graphics)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ft_put_pixel(graphics, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}

void	draw_player(t_player *player);
void	draw_all(t_game *game);

int	deal_key(int key, t_game *game)
{
	if (key == KEY_ESC)
		ft_destroy(game);
	if (key == KEY_A)
		player_move(game->player, 270);
	if (key == KEY_W)
		player_move(game->player, 0);
	if (key == KEY_D)
		player_move(game->player, 90);
	if (key == KEY_S)
		player_move(game->player, 180);
	if (key == KEY_LEFT)
		player_turn_left(game->player);
	if (key == KEY_RIGHT)
		player_turn_right(game->player);
	printf("loc: %lf : %lf\n", game->player->loc.x,
		game->player->loc.y);
	printf("dir: %lf\n", rtd(game->player->direction));
	ft_clear_image(game->graphics);
	draw_all(game);
	return (0);
}
