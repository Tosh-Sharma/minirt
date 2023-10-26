/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:09:10 by toshsharma        #+#    #+#             */
/*   Updated: 2023/10/23 16:15:52 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	my_exit(t_rt *rt)
{
	free(rt->ambient);
	free(rt->light);
	free(rt->sphere);
	free(rt->plane);
	free(rt->cylinder);
	free(rt->cone);
	exit(0);
}

void	perror_and_exit(char *input)
{
	perror(input);
	exit(0);
}

void	free_strings(char **str)
{
	int	i;

	i = -1;
	while (str != NULL && str[++i] != NULL)
		free(str[i]);
	free(str);
	str = NULL;
}

void	copy_colors(int *color_src, int *color_dest)
{
	int	i;

	i = -1;
	while (++i < 3)
		color_dest[i] = color_src[i];
}
