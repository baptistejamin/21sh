/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 16:06:50 by bjamin            #+#    #+#             */
/*   Updated: 2015/12/01 15:44:15 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	start;
	size_t	end;
	char	*str;

	if (!s)
		return (NULL);
	start = 0;
	end = ft_strlen(s) - 1;
	while ((s[start] == ' ' || s[start] == '\t' || s[start] == '\n')
			&& start <= end)
		start++;
	while ((s[end] == ' ' || s[end] == '\t' || s[end] == '\n') && end >= start)
		end--;
	str = ft_strsub(s, start, end - start + 1);
	return (str);
}
