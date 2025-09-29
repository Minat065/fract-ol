/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 10:00:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/09/29 10:00:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_hook(t_data *data)
{
	cleanup(data);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_hook(data);
	else if (keycode == 65362)
		data->fractal.offset_y -= 0.1 / data->fractal.zoom;
	else if (keycode == 65364)
		data->fractal.offset_y += 0.1 / data->fractal.zoom;
	else if (keycode == 65361)
		data->fractal.offset_x -= 0.1 / data->fractal.zoom;
	else if (keycode == 65363)
		data->fractal.offset_x += 0.1 / data->fractal.zoom;
	else if (keycode == 61)
		data->fractal.max_iter += 10;
	else if (keycode == 45 && data->fractal.max_iter > 10)
		data->fractal.max_iter -= 10;
	else if (keycode == 114)
	{
		data->fractal.zoom = 1.0;
		data->fractal.offset_x = 0.0;
		data->fractal.offset_y = 0.0;
	}
	else if (keycode == 99)
		data->fractal.color_scheme = (data->fractal.color_scheme + 1) % 3;
	render_fractal(data);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_data *data)
{
	double	mouse_x;
	double	mouse_y;

	if (button == 4 || button == 5)
	{
		mouse_x = screen_to_complex_x(x, data);
		mouse_y = screen_to_complex_y(y, data);
		if (button == 4)
		{
			data->fractal.zoom *= 1.1;
		}
		else if (button == 5)
		{
			data->fractal.zoom *= 0.9;
		}
		data->fractal.offset_x = mouse_x - (screen_to_complex_x(x, data) - data->fractal.offset_x);
		data->fractal.offset_y = mouse_y - (screen_to_complex_y(y, data) - data->fractal.offset_y);
		render_fractal(data);
	}
	return (0);
}

int	cleanup(t_data *data)
{
	if (data->img.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
		mlx_destroy_display(data->mlx_ptr);
	if (data->mlx_ptr)
		free(data->mlx_ptr);
	exit(0);
	return (0);
}