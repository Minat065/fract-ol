/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 10:00:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/09/29 10:00:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	mandelbrot_calc_smooth(double real, double imag, int max_iter)
{
	double	z_real;
	double	z_imag;
	double	temp;
	int		iter;
	double	z_real_sq;
	double	z_imag_sq;

	z_real = 0.0;
	z_imag = 0.0;
	iter = 0;
	while (iter < max_iter)
	{
		z_real_sq = z_real * z_real;
		z_imag_sq = z_imag * z_imag;
		if (z_real_sq + z_imag_sq > 256.0)
		{
			return (iter + 1 - log(log(sqrt(z_real_sq + z_imag_sq))) / log(2.0));
		}
		temp = z_real_sq - z_imag_sq + real;
		z_imag = 2.0 * z_real * z_imag + imag;
		z_real = temp;
		iter++;
	}
	return (iter);
}

int	mandelbrot_calc(double real, double imag, int max_iter)
{
	return ((int)mandelbrot_calc_smooth(real, imag, max_iter));
}

double	julia_calc_smooth(double real, double imag, t_data *data)
{
	double	z_real;
	double	z_imag;
	double	temp;
	int		iter;
	double	z_real_sq;
	double	z_imag_sq;

	z_real = real;
	z_imag = imag;
	iter = 0;
	while (iter < data->fractal.max_iter)
	{
		z_real_sq = z_real * z_real;
		z_imag_sq = z_imag * z_imag;
		if (z_real_sq + z_imag_sq > 256.0)
		{
			return (iter + 1 - log(log(sqrt(z_real_sq + z_imag_sq))) / log(2.0));
		}
		temp = z_real_sq - z_imag_sq + data->fractal.julia_real;
		z_imag = 2.0 * z_real * z_imag + data->fractal.julia_imag;
		z_real = temp;
		iter++;
	}
	return (iter);
}

int	julia_calc(double real, double imag, t_data *data)
{
	return ((int)julia_calc_smooth(real, imag, data));
}

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