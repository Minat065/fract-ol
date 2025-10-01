/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 23:55:07 by mirokugo          #+#    #+#             */
/*   Updated: 2025/10/02 00:11:36 by mirokugo         ###   ########.fr       */
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
