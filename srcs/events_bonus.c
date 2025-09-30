/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 10:00:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/09/30 20:30:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

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

static int	handle_movement_keys(int keycode, t_data *data)
{
	if (keycode == UP_KEY)
		data->fractal.offset_y -= 0.1 / data->fractal.zoom;
	else if (keycode == DOWN_KEY)
		data->fractal.offset_y += 0.1 / data->fractal.zoom;
	else if (keycode == LEFT_KEY)
		data->fractal.offset_x -= 0.1 / data->fractal.zoom;
	else if (keycode == RIGHT_KEY)
		data->fractal.offset_x += 0.1 / data->fractal.zoom;
	else
		return (0);
	return (1);
}

static int	handle_control_keys(int keycode, t_data *data)
{
	if (keycode == ZOOM_IN_KEY)
		data->fractal.max_iter += 10;
	else if (keycode == ZOOM_OUT_KEY && data->fractal.max_iter > 10)
		data->fractal.max_iter -= 10;
	else if (keycode == COLOR_KEY)
		data->fractal.color_scheme = (data->fractal.color_scheme + 1) % 3;
	else if (keycode == RESET_KEY)
	{
		data->fractal.zoom = 1.0;
		data->fractal.offset_x = 0.0;
		data->fractal.offset_y = 0.0;
	}
	else
		return (0);
	return (1);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		return (close_hook(data));
	if (handle_movement_keys(keycode, data)
		|| handle_control_keys(keycode, data))
		render_fractal(data);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_data *data)
{
	double	mouse_real;
	double	mouse_imag;
	double	zoom_factor;

	if (button == 4 || button == 5)
	{
		mouse_real = screen_to_complex_x(x, data);
		mouse_imag = screen_to_complex_y(y, data);
		if (button == 4)
			zoom_factor = 1.1;
		else
			zoom_factor = 0.9;
		data->fractal.offset_x = mouse_real + (data->fractal.offset_x
				- mouse_real) / zoom_factor;
		data->fractal.offset_y = mouse_imag + (data->fractal.offset_y
				- mouse_imag) / zoom_factor;
		data->fractal.zoom *= zoom_factor;
		render_fractal(data);
	}
	return (0);
}
