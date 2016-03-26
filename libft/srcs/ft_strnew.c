/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 15:04:23 by bjamin            #+#    #+#             */
/*   Updated: 2015/12/01 16:56:10 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char	*tmp;
	size_t	i;

	i = 0;
	tmp = (char *)ft_memalloc(sizeof(char) * (size + 1));
	if (!tmp)
		return (NULL);
	return (tmp);
}
