#include "cub.h"

void	player_set_locdir(t_game *g)
{
	g->player->loc.x = g->parser->map->player_x + 0.5;
	g->player->loc.y = g->parser->map->player_y + 0.5;
	g->player->direction = dtr(g->parser->map->player_dir + 180);
}

void	player_move_N(t_player *p)
{
	int new_y;

	new_y = p->loc.y - p->speed;
	printf("new_y %d\n", new_y);
	if (is_wall(p->game, (int)p->loc.x, new_y))
	{
		printf("collision N\n");
	}
	else
		p->loc.y -= p->speed;
}
void	player_move_S(t_player *p)
{
	int new_y;

	new_y = p->loc.y + p->speed;
	if (is_wall(p->game, (int)p->loc.x, new_y))
	{
		printf("collision S\n");
	}
	else
		p->loc.y += p->speed;
}
void	player_move_E(t_player *p)
{
	int new_x;

	new_x = p->loc.x + p->speed;
	if (is_wall(p->game, new_x, (int)p->loc.y))
	{
		printf("collision E\n");
	}
	else
		p->loc.x += p->speed;
}
void	player_move_W(t_player *p)
{
	int new_x;

	new_x = p->loc.x - p->speed;
	if (is_wall(p->game, new_x, (int)p->loc.y))
	{
		printf("collision W\n");
	}
	else
		p->loc.x -= p->speed;
}

void	player_turn_right(t_player *player)
{
	player->direction += player->rotation_rate;
}

void	player_turn_left(t_player *player)
{
	player->direction -= player->rotation_rate;
}


void	set_sizes(t_game *game, int grid_width, int grid_heigth, int scale)
{
	game->parser->map->columns = grid_width;
	game->parser->map->rows = grid_heigth;
	game->scale = scale;
	game->px_width = game->parser->map->columns * game->scale;
	game->px_heigth = game->parser->map->rows * game->scale;
}