/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:10:29 by mirokugo          #+#    #+#             */
/*   Updated: 2025/10/02 00:10:36 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
