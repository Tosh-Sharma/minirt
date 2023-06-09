/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 13:58:30 by tsharma           #+#    #+#             */
/*   Updated: 2023/06/09 13:58:35 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_ambient	ambient_lightning(t_rt *rt)
{
	t_ambient	ambient;
	char		**split_color;
	int			i;

	if (rt->split_line[3] != NULL)
		perror_and_exit("Extra ambient lightning settings");
	ambient.brightness = ft_atof(rt->split_line[1]);
	if (ambient.brightness > 1.0 || ambient.brightness < 0.0)
		perror_and_exit("Unacceptable ambient brightness value");
	split_color = ft_split(rt->split_line[2], ',');
	if (split_color[3] != NULL)
		perror_and_exit("Unacceptable ambient color values");
	i = -1;
	while (split_color[++i])
	{
		ambient.color[i] = ft_atoi(split_color[i]);
		if (ambient.color[i] > 255 || ambient.color[i] < 0)
			perror_and_exit("Wrong ambient lightning color value");
	}
	free_strings(split_color);
	++rt->ct_a;
	//else QUOI FAIRE?
	return (ambient);
}
