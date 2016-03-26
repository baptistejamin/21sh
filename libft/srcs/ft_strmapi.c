/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 15:48:28 by bjamin            #+#    #+#             */
/*   Updated: 2015/12/09 16:22:11 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_ptr;
	size_t	i;

	if (!s || !f)
		return (NULL);
	i = 0;
	new_ptr = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!new_ptr)
		return (NULL);
	while (s[i])
	{
		new_ptr[i] = f(i, s[i]);
		i++;
	}
	new_ptr[i] = '\0';
	return (new_ptr);
}
