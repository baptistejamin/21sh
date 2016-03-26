/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 12:39:55 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/14 18:58:59 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

char	*ft_strfjoin(char *s1, char *s2)
{
	char *new_str;

	new_str = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	return (new_str);
}
