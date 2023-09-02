/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:16:01 by tsharma           #+#    #+#             */
/*   Updated: 2022/11/11 12:16:24 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	putunbr(unsigned int n, size_t base, char *input)
{
	int			iterator;
	char		c[20];
	char		*str;

	iterator = 0;
	while (n > 0)
	{
		c[iterator] = input[n % base];
		n = n / base;
		iterator++;
	}
	c[iterator] = 0;
	str = ft_revstr(c);
	ft_putstr_fd(str, 1);
	free(str);
	return (iterator);
}

int	pf_putunbr(unsigned int n, char *input)
{
	size_t	base;

	base = ft_strlen(input);
	if (n == 0)
	{
		ft_putchar_fd(input[0], 1);
		return (1);
	}
	else
		return (putunbr(n, base, input));
}
