/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:10:19 by mokatova          #+#    #+#             */
/*   Updated: 2022/12/16 00:55:10 by mokatova         ###   ########.fr       */
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
