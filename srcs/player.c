#include "cub.h"

t_loc	rotate_aroud(t_loc center, float radius, float angle)
{
	t_loc	new;

	new.x = center.x + cos(angle) * radius;
	new.y = center.y + sin(angle) * radius;
	return (new);
}

void	draw_dir(t_player *player)
{
	int	len = 1;
	
	t_loc center = player->loc;
	t_loc tip = rotate_aroud(center, len, player->direction);
	draw_line(center, tip, RED, player->game);
}

void draw_player(t_player *p)
{
	t_loc corner;

	corner = add_vecs(p->loc, (t_loc){-0.5 * PLAYERSIZE, -0.5 * PLAYERSIZE});
	fill_sqare(p->game, corner, p->game->scale * PLAYERSIZE, RED);
	draw_dir(p);
}