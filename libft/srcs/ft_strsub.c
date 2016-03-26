/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 16:04:49 by bjamin            #+#    #+#             */
/*   Updated: 2015/12/01 16:56:29 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*new_str;
	char			*ret;
	unsigned int	i;

	new_str = (char *)malloc(len + 1);
	if (!new_str || !s)
		return (NULL);
	i = start;
	ret = new_str;
	while ((i - start) < len)
	{
		*new_str = s[i];
		new_str++;
		i++;
	}
	*new_str = '\0';
	return (ret);
}
