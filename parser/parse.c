/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:30:22 by mokatova          #+#    #+#             */
/*   Updated: 2022/10/26 13:31:06 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse(t_parser *game, char *file)
{
	int		fd;
	char	*line;

	if (ft_strncmp(&file[ft_strlen(file) - 4], ".cub", 4) != 0)
		quit_game(game, WRNG_ARG, "It seems that the extension is not .cub");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		quit_game(game, errno, "We were unable to open the file:(");
	colors_n_textures(fd, game, &line);
	is_everything_in_place(game);
	parse_map(game, fd, line);
	close(fd);
}

void	colors_n_textures(int fd, t_parser *game, char **line)
{
	game->settings = malloc(sizeof(t_settings));
	game->settings->ceiling_color = -1;
	game->settings->floor_color = -1;
	game->settings->textures[0].ptr = NULL;
	game->settings->textures[1].ptr = NULL;
	game->settings->textures[2].ptr = NULL;
	game->settings->textures[3].ptr = NULL;
	*line = get_next_line(fd);
	while (*line)
	{
		if (*line[0] == 'F')
			set_color(*line, &game->settings->floor_color, game, 1);
		else if (*line[0] == 'C')
			set_color(*line, &game->settings->ceiling_color, game, 1);
		else if (*line[0] == 'N' || *line[0] == 'S'
			|| *line[0] == 'E' || *line[0] == 'W')
			set_textures(*line, game, 2, -1);
		else if (*line[0] != '\0')
			return ;
		free(*line);
		*line = get_next_line(fd);
	}
	free(*line);
}

void	is_everything_in_place(t_parser *game)
{
	if (game->settings->ceiling_color == -1
		|| game->settings->floor_color == -1
		|| !game->settings->textures[0].ptr
		|| !game->settings->textures[1].ptr
		|| !game->settings->textures[2].ptr
		|| !game->settings->textures[3].ptr)
		quit_game(game, MAP_RULES,
			"Colors for ceiling and floor + all 4 textures should be present");
}

void	parse_map(t_parser *game, int fd, char *line)
{
	t_list	*list;

	calculate_map_size(game, fd, line, &list);
	malloc_map(game);
	assign_values(game, list);
	clear_list(&list);
	is_map_ok(game);
	parse_player(game);
}
