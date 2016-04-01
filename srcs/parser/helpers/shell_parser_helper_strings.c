/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parser_helper_strings.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int shell_parser_helper_strings_whitespaces(char **p_input, char *end, char *search)
{
	char *tmp;

	tmp = *p_input;
	while(tmp < end && ft_strchr(WHITESPACES, *tmp))
		tmp++;
	*p_input = tmp;
	return (*tmp && ft_strchr(search, *tmp));
}

int	shell_parser_helper_strings_scan(char **p_input, char *end,
							char *search, char **new_cmd, char **new_cmd_end)
{
	char *tmp;

	tmp = *p_input;
	while (tmp < end && ft_strchr(WHITESPACES, *tmp))
		tmp++;
	*new_cmd = tmp;
	while (tmp < end && !ft_strchr(search, *tmp))
		tmp++;
	*new_cmd_end = tmp;
	*p_input = tmp;
	return (tmp != end);
}