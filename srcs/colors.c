/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 10:00:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/09/29 10:00:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	get_psychedelic_color(double t)
{
	int	r;
	int	g;
	int	b;

	r = (int)(127.5 * (1 + sin(t * 12.0)));
	g = (int)(127.5 * (1 + sin(t * 8.0 + 2.0)));
	b = (int)(127.5 * (1 + sin(t * 16.0 + 4.0)));
	return ((r << 16) | (g << 8) | b);
}

static int	get_sunset_color_part1(double t)
{
	int	r;
	int	g;
	int	b;

	if (t < 0.25)
	{
		r = (int)(255 * (4 * t));
		g = 0;
		b = (int)(128 * (1 - 4 * t));
	}
	else
	{
		r = 255;
		g = (int)(255 * (4 * (t - 0.25)));
		b = 0;
	}
	return ((r << 16) | (g << 8) | b);
}

static int	get_sunset_color_part2(double t)
{
	int	r;
	int	g;
	int	b;

	if (t < 0.75)
	{
		r = (int)(255 * (1 - 4 * (t - 0.5)));
		g = 255;
		b = (int)(255 * (4 * (t - 0.5)));
	}
	else
	{
		r = 0;
		g = (int)(255 * (1 - 4 * (t - 0.75)));
		b = 255;
	}
	return ((r << 16) | (g << 8) | b);
}

int	get_sunset_color(double t)
{
	if (t < 0.5)
		return (get_sunset_color_part1(t));
	else
		return (get_sunset_color_part2(t));
}

int	get_ocean_color(double t)
{
	int	r;
	int	g;
	int	b;

	r = (int)(64 * (1 + sin(t * 6.0)));
	g = (int)(128 + 127 * sin(t * 4.0 + 1.0));
	b = (int)(192 + 63 * sin(t * 8.0 + 2.0));
	return ((r << 16) | (g << 8) | b);
}

int	get_color_smooth(double smooth_iter, int max_iter, int color_scheme)
{
	double	t;

	if (smooth_iter >= max_iter)
		return (0x000000);
	t = smooth_iter / (double)max_iter;
	if (color_scheme == 0)
		return (get_psychedelic_color(t));
	else if (color_scheme == 1)
		return (get_sunset_color(t));
	else
		return (get_ocean_color(t));
}

int	get_color(int iter, int max_iter, int color_scheme)
{
	return (get_color_smooth((double)iter, max_iter, color_scheme));
}