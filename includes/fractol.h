/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:54:59 by mirokugo          #+#    #+#             */
/*   Updated: 2025/09/24 21:29:49 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>
# include <errno.h>
# include "../libft/libft.h"

# define WIDTH 800
# define HEIGHT 600
# define MAX_ITER 100

typedef enum e_fractal_type
{
	MANDELBROT,
	JULIA
}	t_fractal_type;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_fractal
{
	t_fractal_type	type;
	double			zoom;
	double			offset_x;
	double			offset_y;
	double			julia_real;
	double			julia_imag;
	int				max_iter;
	int				color_scheme;
}	t_fractal;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_fractal	fractal;
	int			width;
	int			height;
}	t_data;
void	print_usage(void);
int		run_mandelbrot(void);
int		run_julia(double real, double imag);
int		validate_julia_args(char *real_str, char *imag_str);

int		init_data(t_data *data, t_fractal_type type, double julia_r,
			double julia_i);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	clear_image(t_data *data);
void	render_fractal(t_data *data);

int		key_hook(int keycode, t_data *data);
int		mouse_hook(int button, int x, int y, t_data *data);
int		close_hook(t_data *data);
int		cleanup(t_data *data);

double	screen_to_complex_x(int x, t_data *data);
double	screen_to_complex_y(int y, t_data *data);
int		get_color(int iter, int max_iter, int color_scheme);
int		get_color_smooth(double smooth_iter, int max_iter, int color_scheme);

int		mandelbrot_calc(double real, double imag, int max_iter);
int		julia_calc(double real, double imag, t_data *data);
double	mandelbrot_calc_smooth(double real, double imag, int max_iter);
double	julia_calc_smooth(double real, double imag, t_data *data);
void	draw_mandelbrot(t_data *data);
void	draw_julia(t_data *data);

#endif