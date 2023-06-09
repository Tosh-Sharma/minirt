/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 13:51:45 by tsharma           #+#    #+#             */
/*   Updated: 2023/06/09 13:55:54 by tsharma          ###   ########.fr       */
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

float	ft_atof(const char *str)
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
		return ((float)(res + res2));
	else
		return ((float)(res - res2));
}
