/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 13:17:16 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/14 18:59:00 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

int		ft_strcut(char **s1, char **s2, char c)
{
	char	*tmp;
	char	*ret;
	size_t	len;

	len = 0;
	ret = ft_strdup(*s2);
	while (ret[len] && ret[len] != c)
		len++;
	ret[len] = 0;
	*s1 = ret;
	tmp = ft_strsub(*s2, ft_strlen(*s1) + 1, ft_strlen(*s2) - ft_strlen(*s1));
	if (s2 && *s2)
		free(*s2);
	*s2 = ft_strdup(tmp);
	if (tmp)
		free(tmp);
	return (1);
}
