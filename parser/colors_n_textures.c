/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_n_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:09:46 by mokatova          #+#    #+#             */
/*   Updated: 2022/10/12 13:55:11 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	set_color(char *line, int *color, t_parser *game, int i)
{
	char	**colors;
	int		rgb[3];

	if (*color != -1)
	{
		free(line);
		quit_game(game, MAP_RULES, "Only one color per floor and ceiling");
	}
	while (line[i] == ' ')
		i++;
	colors = ft_split(&line[i], ',');
	if (!colors[0] || !colors[1] || !colors[2] || colors[3])
	{
		free(line);
		free_array(colors);
		quit_game(game, MAP_RULES, "Make sure the color format is correct");
	}
	if (are_colors_valid(colors, rgb) == -1)
	{
		free(line);
		free_array(colors);
		quit_game(game, MAP_RULES, "Make sure the color format is correct");
	}
	free_array(colors);
	*color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
}

int	are_colors_valid(char **colors, int *rgb)
{
	rgb[0] = cub_atoi(colors[0]);
	rgb[1] = cub_atoi(colors[1]);
	rgb[2] = cub_atoi(colors[2]);

	if (rgb[0] > 255 || rgb[1] > 255 || rgb[2] > 255
		|| rgb[0] < 0 || rgb[1] < 0 || rgb[2] < 0)
		return (-1);
	return (0);
}

int	cub_atoi(char *color)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	if (ft_strlen(color) > 10)
		return (-1);
	while (color[i])
	{
		if (color[i] != ' ' && color[i] != '+' && color[i] != '\n'
			&& !(color[i] <= '9' && color[i] >= '0'))
			return (-1);
		i++;
	}
	i = 0;
	while (color[i] == ' ')
		i++;
	if (color[i] == '+')
		i++;
	while (color[i] <= '9' && color[i] >= '0')
	{
		result *= 10;
		result += color[i++] - '0';
	}
	return (result);
}

void	set_textures(char *line, t_parser *game, int j, int i)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		i = 0;
	else if (ft_strncmp(line, "SO", 2) == 0)
		i = 1;
	else if (ft_strncmp(line, "WE", 2) == 0)
		i = 2;
	else if (ft_strncmp(line, "EA", 2) == 0)
		i = 3;
	else
	{
		free(line);
		quit_game(game, MAP_RULES, "Wrong format of textures' paths");
	}
	if (game->settings->textures[i].ptr)
	{
		free(line);
		quit_game(game, MAP_RULES, "There should be no duplicates in textures");
	}
	while (line[j] == ' ')
		j++;
	if (import_textures(&line[j], &game->settings->textures[i], game) != 0)
	{
		free(line);
		quit_game(game, MAP_RULES, "Check that texture's extension is .xpm");
	}
}

int	import_textures(char *line, t_image *texture, t_parser *game)
{
	char	*tmp;

	tmp = ft_substr(line, 0, ft_strlen(line));
	if (ft_strncmp(&line[ft_strlen(line) - 4], ".xpm", 4) == 0)
		texture->ptr = mlx_xpm_file_to_image(game->mlx, tmp,
				&texture->width, &texture->height);
	else
		return (-1);
	texture->addr = mlx_get_data_addr(texture->ptr, &texture->bpp,
			&texture->llen, &texture->endian);
	free(tmp);
	return (0);
}
