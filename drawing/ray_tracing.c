/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:28:49 by toshsharma        #+#    #+#             */
/*   Updated: 2023/09/03 11:30:58 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	iterate_over_objects(t_rt *rt, t_ray ray, double *t)
{
	t_uint	i;

	i = -1;
	while (++i < rt->max_sp)
		intersect_sphere(rt->sphere[i], ray, t);
	// i = -1;
	// while (++i < rt->max_cy)
	// 	intersect_cylinder(rt->cylinder[i], ray, t);
	// i = -1;
	// while (++i < rt->max_pl)
	// 	intersect_plane(rt->plane[i], ray, t);
}
// TODO: Add below cone logic above when all others are working correctly.
// i = -1;
// while (++i < rt->max_cone)
// 	intersect_cone(rt->cone[i], ray, t);

t_ray	generate_ray(t_rt *rt, t_ray ray, int i, int j)
{
	double		x;
	double		y;

	x = 2.0f * ((i + 0.5f) / WIDTH) - 1.0f;
	y = 1.0f - (2.0f * ((j + 0.5f) / HEIGHT));
	ray.direction = vec_add(rt->img.forward, vec_add(
				scalar_product(rt->img.right, x * rt->img.width),
				scalar_product(rt->img.up, y * rt->img.height)));
	ray.direction = normalize_vector(ray.direction);
	return (ray);
}

void	cast_rays(t_rt *rt)
{
	int		i;
	int		j;
	double	t;
	t_ray	ray;

	j = 0;
	set_up_vector_directions(rt);
	ray.origin = return_vector(rt->camera.origin.x, rt->camera.origin.y,
			rt->camera.origin.z);
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			t = INFINITY;
			ray = generate_ray(rt, ray, i, j);
			iterate_over_objects(rt, ray, &t);
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
	put_pixel(rt->img.img, WIDTH / 2, HEIGHT / 2, 0x0066FFFF);
	// cast_rays(rt);
	mlx_put_image_to_window(rt->img.mlx, rt->img.mlx_win, rt->img.img, 0, 0);
	mlx_hook(rt->img.mlx_win, 17, 0, &exit_hook, &rt->img);
	mlx_loop(rt->img.mlx);
}