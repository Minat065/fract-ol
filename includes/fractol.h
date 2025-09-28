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

#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>
#include "../libft/libft.h"

//ここに定数の定義

//ここに構造体の定義

//ここに関数プロトタイプ宣言
void print_usage(void);
int run_mandelbrot(void);
int run_julia(double real, double imag);

//ここにenumの定義

//ここにtypedefの定義

//ここsにマクロの定義

#endif