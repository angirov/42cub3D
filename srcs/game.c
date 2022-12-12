#include "cub.h"

void	player_set_locdir(t_game *g)
{
	g->player->loc.x = g->parser->map->player_x + 0.5;
	g->player->loc.y = g->parser->map->player_y + 0.5;
	g->player->direction = dtr(g->parser->map->player_dir + 180);
}

void	player_turn_right(t_player *player)
{
	player->direction += player->rotation_radian;
}

void	player_turn_left(t_player *player)
{
	player->direction -= player->rotation_radian;
}


void	set_sizes(t_game *game, int grid_width, int grid_heigth, int scale)
{
	game->parser->map->columns = grid_width;
	game->parser->map->rows = grid_heigth;
	game->scale = scale;
	game->px_width = game->parser->map->columns * game->scale;
	game->px_heigth = game->parser->map->rows * game->scale;
}

void	player_move(t_player *p, int dir_grades)
{
	t_loc new_loc;
	t_loc dir_vec;

	dir_vec = dir2vec(p->direction + dtr(dir_grades));
	new_loc = add_vecs(p->loc, sc_mult(dir_vec, p->speed));
	if (is_wall(p->game, (int)new_loc.x, (int)new_loc.y))
	{
		printf("collision N\n"); ////////////////////////////////////
	}
	else
		p->loc = new_loc;
}
