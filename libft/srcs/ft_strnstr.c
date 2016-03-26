/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 14:51:29 by bjamin            #+#    #+#             */
/*   Updated: 2015/11/27 12:39:23 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t i;
	size_t len;

	i = 0;
	if (!n)
		return (NULL);
	if (*s2 == '\0')
		return ((char *)s1);
	len = ft_strlen(s2);
	while (*s1 && i <= (n - len) && n >= len)
	{
		if (ft_strncmp(s1, s2, len) == 0)
			return ((char *)s1);
		s1++;
		i++;
	}
	return (NULL);
}
