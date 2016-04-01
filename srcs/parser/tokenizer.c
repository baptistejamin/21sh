/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokonizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static int tokonizer_redirection(char **s, int ret)
{
	(*s)++;
	if(**s == '>')
	{
		(*s)++;
		return ('+');
	}
	return (ret);
}

static int tokonizer_aggregators(char **s, int ret)
{
	if(*(*s+1) == '>')
	{
		if(*(*s+2) == '>')
		{
			ret = (**s == '1') ? '+' : '/';  
			*s += 3;    
		}
		else
		{
			ret = (**s == '1') ? '>' : '*';
			*s += 2;
		}
	}
	return (ret);
}

static int tokonizer_string(char **s, char *end)
{
	while(*s < end && !ft_strchr(WHITESPACES, **s) &&
		!ft_strchr(TOKENS, **s))
		s++;
	return ('a');
}

int tokonizer(char **p_input, char *end, char **new_cmd, char **new_cmd_end)
{
	char *s;
	int ret;
	
	s = *p_input;
	while(s < end && strchr(WHITESPACES, *s))
		s++;
	if(new_cmd)
		*new_cmd = s;
	ret = *s;
	if (*s && ft_is_in("|();&<", *s))
		s++;
	else if (*s && ft_is_in(">", *s))
		ret = tokonizer_redirection(&s, ret);
	else if (*s && ft_is_in("12", *s))
		ret = tokonizer_aggregators(&s, ret);
	else
		ret = tokonizer_string(&s, end);
	if(new_cmd_end)
		*new_cmd_end = s;
	while(s < end && ft_strchr(WHITESPACES, *s))
		s++;
	*p_input = s;
	return (ret);
}
