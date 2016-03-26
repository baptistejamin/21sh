/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 18:12:28 by bjamin            #+#    #+#             */
/*   Updated: 2015/11/26 18:16:12 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	char	*ret;
	size_t	i;

	ret = dst;
	i = 0;
	while (*src && i < n)
	{
		*dst = *src;
		i++;
		src++;
		dst++;
	}
	while (i < n)
	{
		*dst = '\0';
		dst++;
		i++;
	}
	return (ret);
}
