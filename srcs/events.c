/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:11:46 by mirokugo          #+#    #+#             */
/*   Updated: 2025/10/02 00:11:52 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_hook(t_data *data)
{
	cleanup(data);
	return (0);
}

int	expose_hook(t_data *data)
{
	render_fractal(data);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		return (close_hook(data));
	return (0);
}

int	mouse_hook(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == 4)
		data->fractal.zoom *= 1.1;
	else if (button == 5)
		data->fractal.zoom *= 0.9;
	else
		return (0);
	render_fractal(data);
	return (0);
}
