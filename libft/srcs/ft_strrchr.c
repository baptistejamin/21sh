/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 16:25:57 by bjamin            #+#    #+#             */
/*   Updated: 2015/11/27 14:32:00 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	ptr = ptr + ft_strlen(ptr);
	while (*ptr != (char)c && ptr != s)
		ptr--;
	if (*ptr == (char)c)
		return (ptr);
	return (NULL);
}
