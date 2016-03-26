/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 11:31:19 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/14 18:59:03 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstcpy(t_list **dest, t_list *src)
{
	while (src)
	{
		ft_lstadd(dest, ft_lstnew(src->content, src->content_size));
		src = src->next;
	}
}
