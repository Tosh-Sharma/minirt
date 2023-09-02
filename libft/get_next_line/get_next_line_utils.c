/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:39:49 by tsharma           #+#    #+#             */
/*   Updated: 2022/11/11 11:00:51 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strchr_int(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if (s[i] == (char)c)
		return (i);
	return (-1);
}

static char	*join_strings(char const *s1,
	char const *s2, char *res, int s1_len)
{
	int		i;
	int		s2_len;

	i = 0;
	s2_len = ft_strlen(s2);
	if (s1 != NULL)
	{
		while (i < s1_len)
		{
			res[i] = s1[i];
			i++;
		}
	}
	i = 0;
	if (s2 != NULL)
	{
		while (i < s2_len)
		{
			res[s1_len + i] = s2[i];
			i++;
		}
	}
	res[s1_len + i] = '\0';
	return (res);
}

char	*ft_strjoin_and_free(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*res;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!res)
		return (NULL);
	res = join_strings(s1, s2, res, s1_len);
	free((void *)s1);
	free((void *)s2);
	return (res);
}

char	*ft_calloc_char(int count, int size)
{
	char	*res;
	int		i;

	res = (char *)malloc(count * size);
	if (!res)
		return (NULL);
	i = 0;
	while (i < count)
	{
		res[i] = 0;
		i++;
	}
	return (res);
}
