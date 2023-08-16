/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:28:49 by toshsharma        #+#    #+#             */
/*   Updated: 2023/08/16 14:36:31 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	iterate_over_objects(t_rt *rt, t_ray ray, float t)
{
	// t_sphere	*sphere;
	// t_plane		*plane;
	// t_cylinder	*cylinder;

	// sphere = rt->sphere;
	// while (sphere)
	// {
	// 	if (intersect_sphere(sphere, ray, &t))
	// 		break ;
	// 	sphere = sphere->next;
	// }
}

t_ray	generate_ray(t_rt *rt, t_ray ray, int i, int j)
{
	ray.origin = return_vector(rt->camera.origin.x, rt->camera.origin.y,
			rt->camera.origin.z);
	// ray.direction = 
}

void	cast_rays(t_rt *rt)
{
	int		i;
	int		j;
	float	t;
	t_ray	ray;

	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			t = INFINITY;
			ray = generate_ray(rt, ray, i, j);
			iterate_over_objects(rt, ray, t);
			++i;
		}
		++j;
	}
}

void	ray_tracing(t_rt *rt)
{
	rt->img.mlx = mlx_init();
	rt->img.mlx_win = mlx_new_window(rt->img.mlx, WIDTH, HEIGHT, "miniRT");
	rt->img.img = mlx_new_image(rt->img.mlx, WIDTH, HEIGHT);
	rt->img.addr = mlx_get_data_addr(rt->img.img, &rt->img.bits_per_pixel,
			&rt->img.line_length, &rt->img.endian);
	cast_rays(rt);
	mlx_put_image_to_window(rt->img.mlx, rt->img.mlx_win, rt->img.img, 0, 0);
	mlx_hook(rt->img.mlx_win, 17, 0, &exit_hook, &rt->img);
	mlx_loop(rt->img.mlx);
}
