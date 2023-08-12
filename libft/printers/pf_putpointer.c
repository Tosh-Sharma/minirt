/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:37:57 by tsharma           #+#    #+#             */
/*   Updated: 2022/11/11 12:16:40 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	pf_putpointer(unsigned long l)
{
	char			res[20];
	unsigned long	i;
	char			*str;
	char			*str2;

	i = 0;
	if (l == 0)
		res[i++] = '0';
	while (l > 0)
	{
		res[i] = "0123456789abcdef"[l % 16];
		i++;
		l = l / 16;
	}
	res[i] = '\0';
	str = ft_revstr(res);
	str2 = ft_strjoin("0x", str);
	ft_putstr_fd(str2, 1);
	free(str);
	free(str2);
	return (i + 2);
}
