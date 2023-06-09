/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:08:09 by tsharma           #+#    #+#             */
/*   Updated: 2022/11/11 12:16:47 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	handle_neg(char *str, int is_neg, int iterator)
{
	if (is_neg == 1)
	{
		ft_putstr_fd("-", 1);
		iterator++;
	}
	ft_putstr_fd(str, 1);
	free(str);
	return (iterator);
}

int	putnbr_fd(int n, size_t base, char *input)
{
	int			iterator;
	char		c[20];
	int			is_neg;
	char		*str;

	iterator = 0;
	is_neg = 0;
	if (n < 0)
	{
		is_neg = 1;
		n *= -1;
	}
	while (n > 0)
	{
		c[iterator] = input[n % base];
		n = n / base;
		iterator++;
	}
	c[iterator] = 0;
	str = ft_revstr(c);
	return (handle_neg(str, is_neg, iterator));
}

int	pf_putnbr(int n, char *input)
{
	size_t	base;

	base = ft_strlen(input);
	if (base == 10 && n == -2147483648)
	{
		ft_putstr_fd("-2147483648", 1);
		return (11);
	}
	else if (n == 0)
	{
		ft_putchar_fd(input[0], 1);
		return (1);
	}
	else
		return (putnbr_fd(n, base, input));
}
