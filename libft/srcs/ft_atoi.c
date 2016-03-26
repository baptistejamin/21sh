/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 14:48:35 by bjamin            #+#    #+#             */
/*   Updated: 2015/11/27 14:30:13 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	char	*ptr;
	int		is_neg;
	int		result;

	result = 0;
	ptr = (char *)str;
	is_neg = 0;
	while (*ptr == ' ' || *ptr == '\t' || *ptr == '\v'
			|| *ptr == '\n' || *ptr == '\f' || *ptr == '\r')
		ptr++;
	if (*ptr == '-' || *ptr == '+')
	{
		if (*ptr == '-')
			is_neg = 1;
		ptr++;
	}
	while (*ptr && *ptr >= '0' && *ptr <= '9')
	{
		result *= 10;
		result += *ptr - '0';
		ptr++;
	}
	if (is_neg)
		result *= -1;
	return (result);
}
