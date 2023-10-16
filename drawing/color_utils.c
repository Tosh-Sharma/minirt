/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:38:41 by toshsharma        #+#    #+#             */
/*   Updated: 2023/10/12 11:11:38 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	add_two_colors(int c1[3], double a, int c2[3], double b)
{
	int	result;

	result = clamp((int)(((c1[0] * a) + (c2[0] * b))), 0, 255) << 16
		| clamp((int)(((c1[1] * a) + (c2[1] * b))), 0, 255) << 8
		| clamp((int)(((c1[2] * a) + (c2[2] * b))), 0, 255);
	return (result);
}

int	array_to_int(int c[3], double a)
{
	int	result;

	result = (int)(c[0] * a) << 16 | (int)(c[1] * a) << 8 | (int)(c[2] * a);
	return (result);
}
