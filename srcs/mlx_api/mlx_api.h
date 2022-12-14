/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_api.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:08:22 by mokatova          #+#    #+#             */
/*   Updated: 2022/12/16 22:27:38 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_API_H
# define MLX_API_H

# if defined(__linux__)
// #  include "libft.h"
#  include "../minilibx-linux/mlx.h"
#  include "../minilibx-linux/mlx_int.h"
#  include "../libft/libft.h"

#  include <stdlib.h>
// #  include <mlx.h>
#  define KEY_ESC 65307
#  define KEY_LEFT 65361
#  define KEY_UP 65362
#  define KEY_RIGHT 65363
#  define KEY_DOWN 65364
#  define KEY_Q 113
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_Z 122
#  define KEY_X 120
#  define KEY_1 49
#  define KEY_2 50
#  define KEY_3 51
#  define KEY_4 52
#  define KEY_P 112
#  define KEY_I 105
#  define KEY_C 99
#  define KEY_D 100

# elif defined(__APPLE__)
#  include <stdlib.h>
#  include "../minilibx_mac/mlx.h"
#  include "../libft/libft.h"

#  define KEY_ESC 53
#  define KEY_LEFT 123
#  define KEY_UP 126
#  define KEY_RIGHT 124
#  define KEY_DOWN 125
#  define KEY_Q 12
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_Z 6
#  define KEY_X 7
#  define KEY_1 18
#  define KEY_2 19
#  define KEY_3 20
#  define KEY_4 21
#  define KEY_P 35
#  define KEY_I 34
#  define KEY_C 8
#  define KEY_D 2

# endif

typedef struct s_graphics
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_prt;
	char	*img_addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		screen_width;
	int		screen_height;
	int		scale;
}	t_graphics;

void	api_put_pixel(t_graphics *data, int x, int y, int color);

void	api_free_graphics(void *mlx_ptr, void *win_ptr, void *img_prt);

#endif