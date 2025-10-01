/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:09:18 by mirokugo          #+#    #+#             */
/*   Updated: 2025/10/02 00:09:26 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_BONUS_H
# define FRACTOL_BONUS_H

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
# define ESC_KEY 65307
# define ZOOM_IN_KEY 61
# define ZOOM_OUT_KEY 45
# define RESET_KEY 114
# define COLOR_KEY 99
# define UP_KEY 65362
# define DOWN_KEY 65364
# define LEFT_KEY 65361
# define RIGHT_KEY 65363

typedef enum e_fractal_type
{
	MANDELBROT,
	JULIA,
	TRICORN
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
int		run_tricorn(void);
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
int		expose_hook(t_data *data);
int		cleanup(t_data *data);

double	screen_to_complex_x(int x, t_data *data);
double	screen_to_complex_y(int y, t_data *data);
int		get_color_smooth(double smooth_iter, int max_iter, int color_scheme);
int		get_psychedelic_color(double t);
int		get_sunset_color(double t);
int		get_ocean_color(double t);

double	mandelbrot_calc_smooth(double real, double imag, int max_iter);
double	julia_calc_smooth(double real, double imag, t_data *data);
double	tricorn_calc_smooth(double real, double imag, int max_iter);
void	draw_mandelbrot(t_data *data);
void	draw_julia(t_data *data);
void	draw_tricorn(t_data *data);

#endif