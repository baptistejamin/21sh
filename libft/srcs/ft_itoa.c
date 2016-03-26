/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 16:07:57 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/14 18:59:04 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

static int		ft_nblen_internal(int nb)
{
	int	len;

	len = 0;
	if (nb < 0)
	{
		len++;
		nb *= -1;
	}
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

static	void	ft_putnbr_buffer(int nb, char *str, int *index)
{
	if (nb == -2147483648)
	{
		ft_strcpy(str, "-2147483648");
		*index = 11;
		return ;
	}
	if (nb < 0)
	{
		str[*index] = '-';
		nb *= -1;
		(*index)++;
	}
	if (nb >= 10)
		ft_putnbr_buffer(nb / 10, str, index);
	str[*index] = nb % 10 + '0';
	(*index)++;
}

char			*ft_itoa(int n)
{
	char	*tmp;
	int		index;

	tmp = (char *)malloc(ft_nblen_internal(n) + 1);
	if (!tmp)
		return (NULL);
	*tmp = '\0';
	index = 0;
	if (!tmp)
		return (NULL);
	ft_putnbr_buffer(n, tmp, &index);
	tmp[index] = '\0';
	return (tmp);
}
