/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvincile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:18:50 by tvincile          #+#    #+#             */
/*   Updated: 2022/04/25 17:42:30 by tvincile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdarg.h>
# include "libft/libft.h"
# include "minirt.h"

int		ft_find_index(char *str, int c);
char	*ft_gnl_strjoin(char *s1, char *s2);
char	*ft_gnl_extra(char *save);
char	*ft_get_line(char *save);
char	*ft_read(int fd, char *save);
char	*get_next_line(int fd);

#endif
