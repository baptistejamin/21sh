/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_at.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 11:31:19 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/14 19:01:52 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstadd_at(t_list **lst, t_list *new, int at)
{
	int		i;
	t_list	*tmp;

	i = 1;
	tmp = *lst;
	while (i <= (at - 1))
	{
		tmp = tmp->next;
		if (tmp == NULL)
			break ;
		i++;
	}
	if (tmp != NULL)
	{
		new->next = tmp->next;
		tmp->next = new;
	}
	else
	{
		ft_lstadd(lst, new);
	}
}
