/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 16:06:06 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/14 18:58:58 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *new_str;

	if (!s1 || !s2)
		return (NULL);
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(s1)
		+ ft_strlen(s2) + 1));
	if (!new_str)
		return (NULL);
	new_str[0] = '\0';
	ft_strcat(new_str, s1);
	ft_strcat(new_str, s2);
	return (new_str);
}
