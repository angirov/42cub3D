#include "cub.h"

void	set_step_side_dist_true(t_game *g, t_raycast *rc, int x)
{
	int	map_x;
	int	map_y;

	map_x = rc->map_x;
	map_y = rc->map_y;
	if (g->ray_dirs[x].x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_true.x = (g->player->loc.x - map_x) * rc->delta_true.x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_true.x = (map_x + 1.0 - g->player->loc.x) * rc->delta_true.x;
	}
	if (g->ray_dirs[x].y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_true.y = (g->player->loc.y - map_y) * rc->delta_true.y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_true.y = (map_y + 1.0 - g->player->loc.y) * rc->delta_true.y;
	}
}

void	set_side_dist_true(t_game *g, t_raycast *rc, int x, int side)
{
	if (side == 0)
		rc->side_dist_true.x = (rc->side_dist_true.x - rc->delta_true.x);
	else
		rc->side_dist_true.y = (rc->side_dist_true.y - rc->delta_true.y);
	if (rc->side_dist_true.x < rc->side_dist_true.y)
		g->distances_true[x] = rc->side_dist_true.x;
	else
		g->distances_true[x] = rc->side_dist_true.y;
}
