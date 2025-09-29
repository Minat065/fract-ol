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

int	mandelbrot_calc(double real, double imag, int max_iter)
{
	double	z_real;
	double	z_imag;
	double	temp;
	int		iter;

	z_real = 0.0;
	z_imag = 0.0;
	iter = 0;
	while (iter < max_iter && (z_real * z_real + z_imag * z_imag) <= 4.0)
	{
		temp = z_real * z_real - z_imag * z_imag + real;
		z_imag = 2.0 * z_real * z_imag + imag;
		z_real = temp;
		iter++;
	}
	return (iter);
}

int	julia_calc(double real, double imag, t_data *data)
{
	double	z_real;
	double	z_imag;
	double	temp;
	int		iter;

	z_real = real;
	z_imag = imag;
	iter = 0;
	while (iter < data->fractal.max_iter 
		&& (z_real * z_real + z_imag * z_imag) <= 4.0)
	{
		temp = z_real * z_real - z_imag * z_imag + data->fractal.julia_real;
		z_imag = 2.0 * z_real * z_imag + data->fractal.julia_imag;
		z_real = temp;
		iter++;
	}
	return (iter);
}

void	draw_mandelbrot(t_data *data)
{
	int		x;
	int		y;
	double	complex_x;
	double	complex_y;
	int		iter;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			complex_x = screen_to_complex_x(x, data);
			complex_y = screen_to_complex_y(y, data);
			iter = mandelbrot_calc(complex_x, complex_y, data->fractal.max_iter);
			my_mlx_pixel_put(data, x, y, get_color(iter, data->fractal.max_iter, data->fractal.color_scheme));
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
	int		iter;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			complex_x = screen_to_complex_x(x, data);
			complex_y = screen_to_complex_y(y, data);
			iter = julia_calc(complex_x, complex_y, data);
			my_mlx_pixel_put(data, x, y, get_color(iter, data->fractal.max_iter, data->fractal.color_scheme));
			x++;
		}
		y++;
	}
}