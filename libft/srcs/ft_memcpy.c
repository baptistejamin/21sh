/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 11:22:49 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/14 18:59:02 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_ptr;
	unsigned char	*src_ptr;
	size_t			i;

	dst_ptr = (unsigned char *)dst;
	src_ptr = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		*dst_ptr = *src_ptr;
		dst_ptr++;
		src_ptr++;
		i++;
	}
	return (dst);
}
