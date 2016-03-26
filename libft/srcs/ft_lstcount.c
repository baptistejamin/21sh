/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 11:24:07 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/14 18:59:03 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

int	ft_lstcount(t_list *list)
{
	int		count;

	count = 0;
	while (list)
	{
		list = list->next;
		count++;
	}
	return (count);
}
