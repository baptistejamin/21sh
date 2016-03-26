/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 14:58:10 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/14 18:59:02 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

void	*ft_memalloc(size_t size)
{
	unsigned char *ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, size);
	return (ptr);
}
