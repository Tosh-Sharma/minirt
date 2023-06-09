/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:17:44 by tsharma           #+#    #+#             */
/*   Updated: 2022/11/11 12:15:46 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	handle_spaces(const char *s, va_list args, size_t *i)
{
	int	n;
	int	count;

	count = 0;
	if (s[0] == 'd' || s[0] == 'i')
	{
		n = va_arg(args, int);
		if (n >= 0)
		{
			ft_putchar_fd(' ', 1);
			count = count + 1;
		}
		count += pf_putnbr(n, "0123456789");
	}
	*i = *i + 2;
	return (count);
}
