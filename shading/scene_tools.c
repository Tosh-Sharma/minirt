#include "../minirt.h"

double	get_specular_factor(t_rt *rt, t_vector normal, t_ray ray, double *t)
{
	t_vector	cam;
	t_vector	incident_ray;
	t_vector	calcul;
	double		dot_prod;
	double		result;

	incident_ray = normalize_vector(vec_subtract(vec_add(ray.origin, scalar_product(ray.direction, *t)), rt->light->origin));
	dot_prod = dot_product(normal, incident_ray);
	calcul = scalar_product(normal, 2.0 * dot_prod);
	calcul = vec_subtract(calcul, incident_ray);
	cam = normalize_vector(vec_subtract(rt->camera.origin,
			vec_add(ray.origin, scalar_product(ray.direction, *t))));
	result = max_num(0.0, dot_product(calcul, scalar_product(cam, -1.0)));
	result = pow(result, 64);
	return (result);
}

double	dist_ratio_rt(t_rt *rt, t_vector light)
{
	double	distance;
	double	factor;

	factor = 500 * rt->light->brightness;
	distance = vec_magnitude(light);
	if (distance < 0)
		distance *= -1;
	if (distance > (factor))
		return (0.0);
	else
		return (1 - (distance / factor));
}
