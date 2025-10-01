/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 22:19:48 by mirokugo          #+#    #+#             */
/*   Updated: 2025/10/02 00:12:21 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

int	main(int argc, char **argv)
{
	if (argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 11))
		run_mandelbrot();
	else if (argc == 2 && !ft_strncmp(argv[1], "tricorn", 8))
		run_tricorn();
	else if (argc == 4 && !ft_strncmp(argv[1], "julia", 6))
	{
		if (validate_julia_args(argv[2], argv[3]))
			run_julia(ft_atof(argv[2]), ft_atof(argv[3]));
		else
			return (1);
	}
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
	ft_printf("  tricorn\n");
	ft_printf("  julia [real_part] [imaginary_part]\n");
	ft_printf("Example:\n");
	ft_printf("  ./fractol mandelbrot\n");
	ft_printf("  ./fractol tricorn\n");
	ft_printf("  ./fractol julia -0.7 0.27015\n");
	ft_printf("\nControls:\n");
	ft_printf("  ESC: Exit\n");
	ft_printf("  Arrow keys: Move view\n");
	ft_printf("  Mouse wheel: Zoom (mouse position)\n");
	ft_printf("  +/-: Adjust iteration count\n");
	ft_printf("  R: Reset view\n");
	ft_printf("  C: Change color scheme\n");
}

int	run_mandelbrot(void)
{
	t_data	data;

	if (!init_data(&data, MANDELBROT, 0.0, 0.0))
	{
		ft_printf("Error: Failed to initialize\n");
		return (1);
	}
	render_fractal(&data);
	mlx_hook(data.win_ptr, 12, 0, expose_hook, &data);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_mouse_hook(data.win_ptr, mouse_hook, &data);
	mlx_hook(data.win_ptr, 17, 0, close_hook, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}

int	run_tricorn(void)
{
	t_data	data;

	if (!init_data(&data, TRICORN, 0.0, 0.0))
	{
		ft_printf("Error: Failed to initialize\n");
		return (1);
	}
	render_fractal(&data);
	mlx_hook(data.win_ptr, 12, 0, expose_hook, &data);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_mouse_hook(data.win_ptr, mouse_hook, &data);
	mlx_hook(data.win_ptr, 17, 0, close_hook, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}

int	run_julia(double real, double imag)
{
	t_data	data;

	if (!init_data(&data, JULIA, real, imag))
	{
		ft_printf("Error: Failed to initialize\n");
		return (1);
	}
	render_fractal(&data);
	mlx_hook(data.win_ptr, 12, 0, expose_hook, &data);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_mouse_hook(data.win_ptr, mouse_hook, &data);
	mlx_hook(data.win_ptr, 17, 0, close_hook, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
