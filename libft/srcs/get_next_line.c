/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 14:23:08 by bjamin            #+#    #+#             */
/*   Updated: 2016/02/23 14:23:11 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include <fcntl.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>

int		get_next_line_clear(int ret_val, int *ret, char *str, char *buf)
{
	*ret = 0;
	str = NULL;
	buf[0] = '\0';
	return (ret_val);
}

int		get_next_line(int const fd, char **line)
{
	static t_gnl t[256];

	if (line == NULL || BUFF_SIZE <= 0 || fd < 0 || fd > 255 || t[fd].ret < 0)
		return (-1);
	t[fd].str = (t[fd].ret == 0 || t[fd].str == NULL) ?
		ft_strnew(1) : t[fd].str;
	if (ft_strchr(t[fd].str, '\n') != NULL)
		return (ft_strcut(line, &(t[fd].str), '\n'));
	while ((t[fd].ret = read(fd, t[fd].buf, BUFF_SIZE)) > 0)
	{
		t[fd].buf[t[fd].ret] = '\0';
		t[fd].str = ft_strfjoin(t[fd].str, t[fd].buf);
		if (ft_strchr(t[fd].str, '\n') != NULL)
			return (ft_strcut(line, &(t[fd].str), '\n'));
	}
	if (t[fd].ret < 0)
		return (get_next_line_clear(-1, &(t[fd].ret), t[fd].str, t[fd].buf));
	if (t[fd].ret == 0 && *(t[fd].str) != '\0')
	{
		if (ft_strchr(t[fd].str, '\n') != NULL)
			return (ft_strcut(line, &(t[fd].str), '\n'));
		return (ft_strcut(line, &(t[fd].str), '\0'));
	}
	return (get_next_line_clear(0, &(t[fd].ret), t[fd].str, t[fd].buf));
}
