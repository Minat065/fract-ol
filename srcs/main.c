/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 22:19:48 by mirokugo          #+#    #+#             */
/*   Updated: 2025/09/24 21:35:21 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	if (argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 11))
		run_mandelbrot();
	else if (argc == 4 && !ft_strncmp(argv[1], "julia", 6))
		run_julia(ft_atof(argv[2]),ft_atof(argv[3]));
	else
	{
		print_usage();
		return (1);
	}
	return (0);
}

void	print_usage(void)
{
	ft_printf("Usage: ./fractol [fractal_type] [options]\n");
	ft_printf("Fractal names:\n");
	ft_printf("  mandelbrot\n");
	ft_printf("  julia [real_part] [imaginary_part]\n");
	ft_printf("Example:\n");
	ft_printf("  ./fractol mandelbrot\n");
	ft_printf("  ./fractol julia -0.7 0.27015\n");
	ft_printf("\nControls:\n");
	ft_printf("  ESC: Exit\n");
	ft_printf("  Arrow keys: Move view\n");
	ft_printf("  Mouse wheel: Zoom in/out\n");
	ft_printf("  +/-: Adjust iteration count\n");
	ft_printf("  R: Reset view\n");
	ft_printf("  C: Change color scheme\n");
}

int run_mandelbrot(void)
{
	t_data	data;

	if (!init_data(&data, MANDELBROT, 0.0, 0.0))
	{
		ft_printf("Error: Failed to initialize\n");
		return (1);
	}
	render_fractal(&data);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_mouse_hook(data.win_ptr, mouse_hook, &data);
	mlx_hook(data.win_ptr, 17, 0, close_hook, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}

int run_julia(double real, double imag)
{
	t_data	data;

	if (!init_data(&data, JULIA, real, imag))
	{
		ft_printf("Error: Failed to initialize\n");
		return (1);
	}
	render_fractal(&data);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_mouse_hook(data.win_ptr, mouse_hook, &data);
	mlx_hook(data.win_ptr, 17, 0, close_hook, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}


