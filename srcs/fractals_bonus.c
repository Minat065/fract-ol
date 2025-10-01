/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 10:00:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/10/02 00:11:56 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

static double	calc_smooth_value(double z_sq_sum, int iter)
{
	double	log_zn;
	double	smooth;

	log_zn = log(sqrt(z_sq_sum));
	smooth = iter + 1 - log(log_zn) / log(2.0);
	return (smooth);
}

double	mandelbrot_calc_smooth(double real, double imag, int max_iter)
{
	double	z[2];
	double	z_sq[2];
	double	temp;
	int		iter;

	z[0] = 0.0;
	z[1] = 0.0;
	iter = 0;
	while (iter < max_iter)
	{
		z_sq[0] = z[0] * z[0];
		z_sq[1] = z[1] * z[1];
		if (z_sq[0] + z_sq[1] > 256.0)
			return (calc_smooth_value(z_sq[0] + z_sq[1], iter));
		temp = z_sq[0] - z_sq[1] + real;
		z[1] = 2.0 * z[0] * z[1] + imag;
		z[0] = temp;
		iter++;
	}
	return (iter);
}

double	julia_calc_smooth(double real, double imag, t_data *data)
{
	double	z[2];
	double	z_sq[2];
	double	temp;
	int		iter;

	z[0] = real;
	z[1] = imag;
	iter = 0;
	while (iter < data->fractal.max_iter)
	{
		z_sq[0] = z[0] * z[0];
		z_sq[1] = z[1] * z[1];
		if (z_sq[0] + z_sq[1] > 256.0)
			return (calc_smooth_value(z_sq[0] + z_sq[1], iter));
		temp = z_sq[0] - z_sq[1] + data->fractal.julia_real;
		z[1] = 2.0 * z[0] * z[1] + data->fractal.julia_imag;
		z[0] = temp;
		iter++;
	}
	return (iter);
}

double	tricorn_calc_smooth(double real, double imag, int max_iter)
{
	double	z[2];
	double	z_sq[2];
	double	temp;
	int		iter;

	z[0] = 0.0;
	z[1] = 0.0;
	iter = 0;
	while (iter < max_iter)
	{
		z_sq[0] = z[0] * z[0];
		z_sq[1] = z[1] * z[1];
		if (z_sq[0] + z_sq[1] > 256.0)
			return (calc_smooth_value(z_sq[0] + z_sq[1], iter));
		temp = z_sq[0] - z_sq[1] + real;
		z[1] = -2.0 * z[0] * z[1] + imag;
		z[0] = temp;
		iter++;
	}
	return (iter);
}
