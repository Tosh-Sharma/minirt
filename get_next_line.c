/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvincile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 12:55:05 by tvincile          #+#    #+#             */
/*   Updated: 2022/04/25 18:15:29 by tvincile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*ft_gnl_extra(char *save)
{
	char	*extra;
	int	i;
	int	jol_index;

	jol_index = ft_find_index(save, '\n');
	if (!save[jol_index])
	{	
		free(save);
		return (NULL);
	}
	extra = (char *)malloc(sizeof(char) * (ft_strlen(save) - jol_index + 1));
	if (!extra)
		return (NULL);
	jol_index++;
	i = 0;
	while (save[jol_index] != '\0')
		extra[i++] = save[jol_index++];
	extra[i] = '\0';
	free(save);
	return (extra);
}

char	*ft_get_line(char *save)
{
	char	*str;
	int	i;

	i = 0;
	if (!save || save[i] == '\0')
		return (NULL);
	while (save[i] != '\0' && save[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	//j = 0;
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		str[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		str[i] = save[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_read(int fd, char *save)
{
	char	*buff;
	int		read_index;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	read_index = 1;
	while (!ft_strchr(save, '\n') && read_index != 0)
	{
		read_index = read(fd, buff, BUFFER_SIZE);
		if (read_index == -1)
		{
			free(buff);
			save = NULL;
			return (save);
		}
		buff[read_index] = '\0';
		save = ft_gnl_strjoin(save, buff);
	}
	free(buff);		
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)	
		return (NULL);
	save = ft_read(fd, save);
	if (save == NULL)
		return (NULL);
	line = ft_get_line(save);
	save = ft_gnl_extra(save);
	return (line);
}
