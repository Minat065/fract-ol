/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 19:45:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/10/02 00:12:07 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_mandelbrot(t_data *data)
{
	int		x;
	int		y;
	double	complex_x;
	double	complex_y;
	double	smooth_iter;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			complex_x = screen_to_complex_x(x, data);
			complex_y = screen_to_complex_y(y, data);
			smooth_iter = mandelbrot_calc_smooth(complex_x, complex_y,
					data->fractal.max_iter);
			my_mlx_pixel_put(data, x, y, get_color_smooth(smooth_iter,
					data->fractal.max_iter, data->fractal.color_scheme));
			x++;
		}
		y++;
	}
}

void	draw_julia(t_data *data)
{
	int		x;
	int		y;
	double	complex_x;
	double	complex_y;
	double	smooth_iter;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			complex_x = screen_to_complex_x(x, data);
			complex_y = screen_to_complex_y(y, data);
			smooth_iter = julia_calc_smooth(complex_x, complex_y, data);
			my_mlx_pixel_put(data, x, y, get_color_smooth(smooth_iter,
					data->fractal.max_iter, data->fractal.color_scheme));
			x++;
		}
		y++;
	}
}
