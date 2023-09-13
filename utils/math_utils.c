/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:11:12 by toshsharma        #+#    #+#             */
/*   Updated: 2023/09/12 17:03:21 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	min_num(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

double	max_num(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}
