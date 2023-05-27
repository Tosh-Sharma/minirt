/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvincile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 12:18:45 by tvincile          #+#    #+#             */
/*   Updated: 2022/04/25 17:35:19 by tvincile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_find_index(char *str, int c)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(str))
	{
		if (str[i] == (char)c)
			return (i);	
		i++;
	}
	return (i);
}

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*line;
	
	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if(!s1 || !s2)
		return (NULL);
	line = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!line)
		return (NULL);
/*
	i = -1;
	j = 0;
	if (s1)
	{
		while (s1[++i] != '\0')
			line[i] = s1[i];
	}
	while (s2[j] != '\0')
		line[i++] = s2[j++];

*/
	i = -1;
	while (s1[++i] != '\0')
		line[i] = s1[i];
	j = 0;
	while (s2[j] != '\0')
		line[i++] = s2[j++];
	line[i++] = '\0';
	free(s1);
	return (line);
}
