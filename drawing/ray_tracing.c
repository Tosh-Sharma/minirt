/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:28:49 by toshsharma        #+#    #+#             */
/*   Updated: 2023/09/12 20:26:02 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	iterate_over_objects(t_rt *rt, t_ray ray, double *t)
{
	t_uint	i;

	i = -1;
	while (++i < rt->max_sp)
		intersect_sphere(rt, rt->sphere[i], ray, t);
	i = -1;
	while (++i < rt->max_pl)
		intersect_plane(rt, rt->plane[i], ray, t);
	i = -1;
	while (++i < rt->max_cy)
		intersect_cylinder(rt, rt->cylinder[i], ray, t);
}
// TODO: Add below cone logic above when all others are working correctly.
// i = -1;
// while (++i < rt->max_cone)
// 	intersect_cone(rt->cone[i], ray, t);

t_ray	generate_ray(t_rt *rt, t_ray ray, int i, int j)
{
	double		x;
	double		y;

	x = 2.0 * ((i + 0.5) / (WIDTH)) - 1.0;
	y = 1.0 - (2.0 * ((j + 0.5) / (HEIGHT)));
	ray.direction = vec_add(rt->img.forward, vec_add(
				scalar_product(rt->img.right, x * rt->img.width),
				scalar_product(rt->img.up, y * rt->img.height)));
	ray.direction = normalize_vector(ray.direction);
	ray.x = i;
	ray.y = j;
	ray.flag = 0;
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
	ray.origin = vectorize(rt->camera.origin.x, rt->camera.origin.y,
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
	cast_rays(rt);
	mlx_put_image_to_window(rt->img.mlx, rt->img.mlx_win, rt->img.img, 0, 0);
	mlx_key_hook(rt->img.mlx_win, &key_hook, &rt->img);
	mlx_hook(rt->img.mlx_win, 17, 0, &exit_hook, &rt->img);
	mlx_loop(rt->img.mlx);
}


/*
	Recreate ray tracing code for shadow :
	
	-	starting point : plane (vec_add(ray.origin, scalar_product(ray.direction, *t))
						 sphere (vec_add(ray.origin, scalar_product(ray.direction, *t))
						 cylinder ()
	-	direction ray : vectorize(light.x, light.y, light.z) : light => plane (normalize_vector(vec_subtract(rt->light->origin, vec_add(ray.origin, scalar_product(ray.direction, *t)))))
																		sphere (normalize_vector(vec_subtract(rt->light->origin, vec_add(ray.origin, scalar_product(ray.direction, *t)))))
																		cylinder ()
	-	t becomes the magnitude of the light vector => vec_magnitude(light)
	
	As long as we don't find an intersection magnitude lower than t, we continue.
	If we don't find any, then colorized gets to continue, if we do, dark color.
*/
