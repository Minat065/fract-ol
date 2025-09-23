/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 22:19:48 by mirokugo          #+#    #+#             */
/*   Updated: 2025/09/23 22:08:16 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../indludes/fractol.h>

int	main(int argc, char **argv)
{
	if (argc == 2 && !ft_strcmp(argv[1], "mandelbrot"))
		run_mandelbrot();
	else if (argc == 4 && !ft_strcmp(argv[1], "julia"))
		run_julia(ft_atof(argv[2]),ft_atof(argv[3]));
	else
	{
		print_usage();
		return (1);
	}
	return (0);
}
