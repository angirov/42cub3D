#include "cub.h"

void	player_set_locdir(t_game *g)
{
	g->player->loc.x = g->parser->map->player_x;
	g->player->loc.y = g->parser->map->player_y;
	g->player->direction = dtr(g->parser->map->player_dir + 180);
}

void	player_move_N(t_player *player)
{
	player->loc.y -= player->speed;
}
void	player_move_S(t_player *player)
{
	player->loc.y += player->speed;
}
void	player_move_E(t_player *player)
{
	player->loc.x += player->speed;
}
void	player_move_W(t_player *player)
{
	player->loc.x -= player->speed;
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