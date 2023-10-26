/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:11:12 by toshsharma        #+#    #+#             */
/*   Updated: 2023/10/24 23:35:56 by toshsharma       ###   ########.fr       */
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

int	clamp(int n, int min, int max)
{
	if (n < min)
		return (min);
	if (n > max)
		return (max);
	return (n);
}

void	double_checker(const char *str)
{
	int	i;
	int	max;
	int	dot_flag;
	int	minus_flag;

	i = -1;
	max = ft_strlen(str);
	dot_flag = 0;
	minus_flag = 0;
	while (++i < max)
	{
		if ((str[i] >= 48 && str[i] <= 57) || str[i] == 46 || str[i] == 45)
		{
			if (str[i] == 46)
				dot_flag += 1;
			else if (str[i] == 45)
				minus_flag += 1;
			if (dot_flag > 1 || minus_flag > 1)
				perror_and_exit("wrong value");
		}
		else
			perror_and_exit("wrong value");
	}
}

double	ft_atod(const char *str)
{
	double	res;
	double	res2;
	char	*c;
	int		len;
	int		flag;

	double_checker(str);
	flag = 1;
	c = (char *)str;
	if (c[0] == '-')
		flag *= -1;
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
		return ((double)(res + res2)*flag);
	else
		return ((double)(res - res2));
}
