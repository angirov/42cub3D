/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:10:19 by mokatova          #+#    #+#             */
/*   Updated: 2022/12/15 21:07:52 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_api.h"

#if __linux__

void	api_free_graphics(void *mlx_ptr, void *win_ptr, void *img_prt)
{
	mlx_destroy_image(mlx_ptr, img_prt);
	mlx_destroy_window(mlx_ptr, win_ptr);
	mlx_destroy_display(mlx_ptr);
}

#else

void	api_free_graphics(void *mlx_ptr, void *win_ptr, void *img_prt)
{
	mlx_destroy_image(mlx_ptr, img_prt);
	mlx_destroy_window(mlx_ptr, win_ptr);
}

#endif
///////////////////////////////////////////////////////////

void	api_put_pixel(t_graphics *api_data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < api_data->screen_width
		&& y >= 0 && y < api_data->screen_height)
	{
		dst = api_data->img_addr
			+ (y * api_data->line_length + x * (api_data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

t_graphics	*api_init_graphics(int width, int height, char *title)
{
	t_graphics	*api_data;

	api_data = (t_graphics *)malloc(sizeof(t_graphics));
	api_data->screen_width = width;
	api_data->screen_height = height;
	api_data->mlx_ptr = mlx_init();
	api_data->win_ptr = mlx_new_window(api_data->mlx_ptr, width, height, title);
	api_data->img_prt = mlx_new_image(api_data->mlx_ptr, width, height);
	api_data->img_addr = mlx_get_data_addr(api_data->img_prt,
			&api_data->bits_per_pixel, &api_data->line_length,
			&api_data->endian);
	return (api_data);
}
