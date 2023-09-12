/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:09:10 by toshsharma        #+#    #+#             */
/*   Updated: 2023/09/09 15:36:38 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	my_exit(t_rt *rt)
{
	free(rt);
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

double	ft_atod(const char *str)
{
	double	res;
	double	res2;
	char	*c;
	int		len;

	c = (char *)str;
	res = (double)ft_atoi(c);
	while (*c && *c != '.')
		c++;
	if (*c == '.')
		c++;
	res2 = (double)ft_atoi(c);
	len = ft_strlen(c);
	while (len--)
		res2 /= 10;
	if (res >= 0)
		return ((double)(res + res2));
	else
		return ((double)(res - res2));
}

void	copy_colors(int *color_src, int *color_dest)
{
	int	i;

	i = -1;
	while (++i < 3)
		color_src[i] = color_dest[i];
}
