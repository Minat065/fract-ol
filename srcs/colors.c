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

int	get_psychedelic_color(double t)
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
