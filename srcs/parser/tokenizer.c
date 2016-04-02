/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/02 21:30:20 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static int	tokenizer_redirection(char **s, int ret)
{
	(*s)++;
	if (**s == '>')
	{
		(*s)++;
		return ('+');
	}
	if (**s == '<')
	{
		(*s)++;
		return ('=');
	}
	return (ret);
}

static int	tokenizer_aggregators(char **s, int ret)
{
	if (*(*s + 1) == '>')
	{
		if (*(*s + 2) == '>')
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

static int	tokenizer_string(char **s, char *end)
{
	while (*s < end && !ft_strchr(WHITESPACES, **s) &&
		!ft_strchr(TOKENS, **s))
		(*s)++;
	return ('a');
}

int			tokenizer(
	char **p_input, char *end, char **new_cmd, char **new_cmd_end)
{
	char	*s;
	int		ret;

	s = *p_input;
	while (s < end && strchr(WHITESPACES, *s))
		s++;
	if (new_cmd)
		*new_cmd = s;
	ret = *s;
	if (*s && ft_is_in("|();&", *s))
		s++;
	else if (*s && ft_is_in("><", *s))
		ret = tokenizer_redirection(&s, ret);
	else if (*s && ft_is_in("12", *s))
		ret = tokenizer_aggregators(&s, ret);
	else if (*s)
		ret = tokenizer_string(&s, end);
	if (new_cmd_end)
		*new_cmd_end = s;
	while (s < end && ft_strchr(WHITESPACES, *s))
		s++;
	*p_input = s;
	return (ret);
}
