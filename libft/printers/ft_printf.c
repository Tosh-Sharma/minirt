/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:12:16 by tsharma           #+#    #+#             */
/*   Updated: 2022/11/11 10:58:55 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	handle_print(const char *s, va_list args, size_t *i)
{
	*i = *i + 1;
	if (s[0] == 'c')
		return (pf_putchar(va_arg(args, int), 1));
	else if (s[0] == 's')
		return (pf_putstr(va_arg(args, char *), 1));
	else if (s[0] == 'p')
		return (pf_putpointer(va_arg(args, unsigned long)));
	else if (s[0] == 'd' || s[0] == 'i')
		return (pf_putnbr(va_arg(args, int), "0123456789"));
	else if (s[0] == 'u')
		return (pf_putunbr(va_arg(args, unsigned int), "0123456789"));
	else if (s[0] == 'x')
		return (pf_putunbr(va_arg(args, unsigned int), "0123456789abcdef"));
	else if (s[0] == 'X')
		return (pf_putunbr(va_arg(args, unsigned int), "0123456789ABCDEF"));
	else if (s[0] == '%')
		return (pf_putchar('%', 1));
	else
		return (pf_putchar(s[0], 1));
}

int	analyse_flags(const char *s, va_list args, size_t *i)
{
	if (s[0] == ' ')
		return (handle_spaces(&s[1], args, i));
	else if (s[0] == '+')
		return (handle_spaces(&s[1], args, i));
	else if (s[0] == '#')
		return (handle_spaces(&s[1], args, i));
	else if (s[0] == '-')
		return (handle_spaces(&s[1], args, i));
	else if (s[0] == '0')
		return (handle_spaces(&s[1], args, i));
	else if (s[0] == '.')
		return (handle_spaces(&s[1], args, i));
	else
		return (handle_print(s, args, i));
}

int	ft_printf(const char *s, ...)
{
	size_t		i;
	va_list		args;
	int			count;

	i = 0;
	count = 0;
	va_start(args, s);
	while (i < ft_strlen(s))
	{
		if (s[i] == '%')
			count += analyse_flags(&s[i + 1], args, &i);
		else
			count += pf_putchar(s[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}
