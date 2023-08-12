/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:48:58 by tsharma           #+#    #+#             */
/*   Updated: 2022/11/11 11:01:01 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*cpy_and_reset_src(char *src)
{
	int		i;
	char	*res;

	i = 0;
	res = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!res)
		return (NULL);
	while (src[i] != '\0')
	{
		res[i] = src[i];
		i++;
	}
	res[i] = '\0';
	src[0] = '\0';
	return (res);
}

char	*break_line(char *line, char *extra, int position)
{
	int		i;
	int		length;
	char	*temp;

	i = 0;
	temp = ft_calloc_char(position + 2, sizeof(char));
	while (i <= position)
	{
		temp[i] = line[i];
		i++;
	}
	temp[i] = '\0';
	i = 0;
	length = ft_strlen(line);
	while (i < length - position)
	{
		extra[i] = line[position + 1 + i];
		i++;
	}
	extra[i] = '\0';
	free(line);
	return (temp);
}

char	*handle_end(char *buffer, char *line)
{
	free(buffer);
	if (ft_strlen(line) > 0)
		return (line);
	else
	{
		free(line);
		return (NULL);
	}
}

char	*handle_read(char *line, char *buffer, char *extra, int fd)
{
	int	read_count;

	read_count = 1;
	while (read_count > 0 || ft_strchr_int(line, '\n') != -1)
	{
		if (ft_strchr_int(line, '\n') != -1)
			return (break_line(line, extra, ft_strchr_int(line, '\n')));
		buffer = ft_calloc_char(BUFFER_SIZE + 1, sizeof(char));
		read_count = read(fd, buffer, BUFFER_SIZE);
		if (read_count == 0)
			return (handle_end(buffer, line));
		if (ft_strchr_int(buffer, '\n') != -1)
		{
			line = ft_strjoin_and_free(line, buffer);
			return (break_line(line, extra, ft_strchr_int(line, '\n')));
		}
		else
			line = ft_strjoin_and_free(line, buffer);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	extra[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = NULL;
	line = cpy_and_reset_src(extra);
	return (handle_read(line, buffer, extra, fd));
}
