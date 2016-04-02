/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static int				prompt_autocompletion_skip_spaces(void)
{
	t_sh	*sh;
	int		start_position;
	t_list	*cur;

	sh = shell_recover();
	while (sh->c_prompt->cursor_index > 0 &&
		sh->c_prompt->cursor_index < sh->c_prompt->lenght)
	{
		cur = ft_lstget_at(
			sh->c_prompt->chars, sh->c_prompt->cursor_index);
		if (cur && !ft_isspace(*(char *)cur->content))
			sh->c_prompt->cursor_index++;
		else
			break ;
	}
	start_position = sh->c_prompt->cursor_index;
	while (start_position > 0)
	{
		cur = ft_lstget_at(sh->c_prompt->chars, start_position - 1);
		if (cur && !ft_isspace(*(char *)cur->content))
			start_position--;
		else
			break ;
	}
	return (start_position);
}

enum e_prompt_status	prompt_autocompletion(char *buf)
{
	t_sh	*sh;
	char	*search;
	int		start_position;
	char	*result;

	sh = shell_recover();
	if (!TAB)
		return (TRYING);
	start_position = prompt_autocompletion_skip_spaces();
	search = shell_prompt_get_command(sh->c_prompt, start_position,
		sh->c_prompt->cursor_index + 1);
	result = shell_autocompletion(search);
	if (result)
	{
		while (result && *result)
		{
			prompt_insert_one_char(*result);
			result++;
		}
	}
	else
		tputs(tgetstr("bl", NULL), 0, tputs_putchar);
	shell_prompt_display(1);
	return (READING);
}
