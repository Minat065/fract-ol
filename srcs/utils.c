/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 10:00:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/10/02 00:12:28 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	screen_to_complex_x(int x, t_data *data)
{
	return ((x - data->width / 2.0) * 4.0
		/ (data->width * data->fractal.zoom) + data->fractal.offset_x);
}

double	screen_to_complex_y(int y, t_data *data)
{
	return ((y - data->height / 2.0) * 4.0
		/ (data->height * data->fractal.zoom) + data->fractal.offset_y);
}
