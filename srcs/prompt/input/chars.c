/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chars.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

enum e_prompt_status	prompt_delete_char(char *buf)
{
	t_sh		*sh;

	sh = shell_recover();
	if (!BACK_SPACE)
		return (TRYING);
	if (sh->c_prompt->cursor_index > 0)
	{
		ft_lstdel_at(
			&sh->c_prompt->chars,
			sh->c_prompt->cursor_index - 1, &free_char);
		sh->c_prompt->cursor_index--;
		sh->c_prompt->lenght--;
		shell_prompt_display(1);
	}
	else
		tputs(tgetstr("bl", NULL), 0, tputs_putchar);
	return (READING);
}

enum e_prompt_status	prompt_delete_next_char(char *buf)
{
	t_sh		*sh;

	sh = shell_recover();
	if (!DELETE)
		return (TRYING);
	if (sh->c_prompt->cursor_index > 0)
	{
		ft_lstdel_at(
			&sh->c_prompt->chars,
			sh->c_prompt->cursor_index, &free_char);
		sh->c_prompt->lenght--;
		shell_prompt_display(1);
	}
	else
		tputs(tgetstr("bl", NULL), 0, tputs_putchar);
	return (READING);
}

void					prompt_insert_one_char(char car)
{
	t_sh		*sh;
	t_list		*new;

	sh = shell_recover();
	new = ft_lstnew(&car, sizeof(char));
	ft_lstadd_at(&sh->c_prompt->chars,
		new, sh->c_prompt->cursor_index);
	sh->c_prompt->cursor_index++;
	sh->c_prompt->lenght++;
}

enum e_prompt_status	prompt_insert_char(char *buf)
{
	if (buf[0])
		prompt_insert_one_char(buf[0]);
	if (buf[1])
		prompt_insert_one_char(buf[1]);
	if (buf[2])
		prompt_insert_one_char(buf[2]);
	shell_prompt_display(1);
	return (READING);
}

enum e_prompt_status	prompt_ignore_input(char *buf)
{
	if (!IGNORE_1)
		return (TRYING);
	return (READING);
}
