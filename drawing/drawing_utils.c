/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:28:47 by toshsharma        #+#    #+#             */
/*   Updated: 2023/09/12 15:05:58 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	free_data(t_image *img)
{
	mlx_destroy_image(img->mlx, img->img);
	mlx_destroy_window(img->mlx, img->mlx_win);
	exit(1);
}

int	key_hook(int keycode, t_image *img)
{
	if (keycode == 53)
		free_data(img);
	return (0);
}

// Add code for freeing all the malloced data.
int	exit_hook(t_image *img)
{
	mlx_destroy_image(img->mlx, img->img);
	mlx_destroy_window(img->mlx, img->mlx_win);
	exit(1);
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

int	array_to_int(int c[3], double a)
{
	int	result;

	result = (int)(a * 255) << 24 | c[0] << 16
		| c[1] << 8 | c[2];
	return (result);
}
