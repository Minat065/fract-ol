/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 10:00:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/09/29 10:00:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_fractal_params(t_data *data, t_fractal_type type)
{
	data->fractal.type = type;
	data->fractal.zoom = 1.0;
	data->fractal.offset_x = 0.0;
	data->fractal.offset_y = 0.0;
	data->fractal.max_iter = MAX_ITER;
	data->fractal.color_scheme = 0;
}

int	init_data(t_data *data, t_fractal_type type, double julia_r, double julia_i)
{
	data->width = WIDTH;
	data->height = HEIGHT;
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (0);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->width,
			data->height, "Fract-ol");
	if (!data->win_ptr)
		return (0);
	data->img.img_ptr = mlx_new_image(data->mlx_ptr,
			data->width, data->height);
	if (!data->img.img_ptr)
		return (0);
	data->img.addr = mlx_get_data_addr(data->img.img_ptr,
			&data->img.bits_per_pixel,
			&data->img.line_length,
			&data->img.endian);
	init_fractal_params(data, type);
	if (type == JULIA)
	{
		data->fractal.julia_real = julia_r;
		data->fractal.julia_imag = julia_i;
	}
	return (1);
}