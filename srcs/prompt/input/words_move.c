/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

enum e_prompt_status	prompt_move_next_word(char *buf)
{
	t_sh		*sh;
	t_list		*cur;

	sh = shell_recover();
	if (!SHIFT_RIGHT)
		return (TRYING);
	while (sh->c_prompt->cursor_index < sh->c_prompt->lenght)
	{
		cur = ft_lstget_at(sh->c_prompt->chars, sh->c_prompt->cursor_index);
		if (cur && !ft_isspace(*(char *)cur->content))
			sh->c_prompt->cursor_index++;
		else
			break ;
	}
	while (sh->c_prompt->cursor_index < sh->c_prompt->lenght)
	{
		cur = ft_lstget_at(sh->c_prompt->chars, sh->c_prompt->cursor_index);
		if (cur && ft_isspace(*(char *)cur->content))
			sh->c_prompt->cursor_index++;
		else
			break ;
	}
	shell_prompt_display(1);
	return (READING);
}

enum e_prompt_status	prompt_move_last_word(char *buf)
{
	t_sh		*sh;
	t_list		*cur;

	sh = shell_recover();
	if (!SHIFT_LEFT)
		return (TRYING);
	while (sh->c_prompt->cursor_index > 0)
	{
		cur = ft_lstget_at(sh->c_prompt->chars, sh->c_prompt->cursor_index - 1);
		if (cur && ft_isspace(*(char *)cur->content))
			sh->c_prompt->cursor_index--;
		else
			break ;
	}
	while (sh->c_prompt->cursor_index > 0)
	{
		cur = ft_lstget_at(
			sh->c_prompt->chars, sh->c_prompt->cursor_index - 1);
		if (cur && !ft_isspace(*(char *)cur->content))
			sh->c_prompt->cursor_index--;
		else
			break ;
	}
	shell_prompt_display(1);
	return (READING);
}
