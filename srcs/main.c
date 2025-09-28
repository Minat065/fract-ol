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

#include <../includes/fractol.h>

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
	ft_printf
	ft_putstr_fd("Fractal names:\n", 2);
	ft_putstr_fd("  mandelbrot\n", 2);
	ft_putstr_fd("  julia [real_part] [imaginary_part]\n", 2);
	ft_putstr_fd("Example:\n", 2);
	ft_putstr_fd("  ./fractol mandelbrot\n", 2);
	ft_putstr_fd("  ./fractol julia -0.7 0.27015\n", 2);
}

int run_mandelbrot(void)
{
	// マンデルブロ集合の描画ロジックをここに実装
	return (0);
}

int run_julia(double real, double imag)
{
	// ジュリア集合の描画ロジックをここに実装
	return (0);
}


