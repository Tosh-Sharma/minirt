/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:28:47 by toshsharma        #+#    #+#             */
/*   Updated: 2023/10/15 17:26:28 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	free_data(t_rt *rt)
{
	mlx_destroy_image(rt->img.mlx, rt->img.img);
	mlx_destroy_window(rt->img.mlx, rt->img.mlx_win);
	my_exit(rt);
}

int	key_hook(int keycode, t_rt *rt)
{
	if (keycode == 53)
		free_data(rt);
	return (0);
}

int	exit_hook(t_rt *rt)
{
	mlx_destroy_image(rt->img.mlx, rt->img.img);
	mlx_destroy_window(rt->img.mlx, rt->img.mlx_win);
	my_exit(rt);
	return (0);
}

void	put_pixel(t_image *data, int x, int y, int color)
{
	char		*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length
			+ x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
