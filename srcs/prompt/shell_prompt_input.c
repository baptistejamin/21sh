/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_prompt_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <stdio.h>

void	free_char(void *content, size_t size)
{
	UNUSED(size);
	free(content);
}

enum e_prompt_status prompt_move_right(char *buf)
{
	t_sh		*sh;
	t_prompt	*prompt;

	sh = shell_recover();

	if (!RIGHT)
		return (TRYING);
	prompt = sh->history->content;
	prompt->cursor_position++;
	tputs(tgetstr("nd", NULL), 0, tputs_putchar);
	return (READING);
}

enum e_prompt_status prompt_move_left(char *buf)
{
	t_sh		*sh;
	t_prompt	*prompt;

	sh = shell_recover();

	if (!LEFT)
		return (TRYING);
	prompt = sh->history->content;
	if (ft_lstcount(prompt->chars) > 0)
	{
		prompt->cursor_position--;
		tputs(tgetstr("le", NULL), 0, tputs_putchar);
	}
	return (READING);
}

enum e_prompt_status prompt_delete_char(char *buf)
{
	t_sh		*sh;
	t_prompt	*prompt;

	sh = shell_recover();

	if (!BACK_SPACE)
		return (TRYING);
	prompt = sh->history->content;
	if (prompt->cursor_position > 0)
	{
		ft_lstdel_at(&prompt->chars, prompt->cursor_position - 1, &free_char);
		prompt->cursor_position--;
		tputs(tgetstr("le", NULL), 0, tputs_putchar);
		shell_prompt_display(sh);
	}
	return (READING);
}

enum e_prompt_status prompt_delete_next_char(char *buf)
{
	t_sh		*sh;
	t_prompt	*prompt;

	sh = shell_recover();

	if (!DELETE)
		return (TRYING);
	prompt = sh->history->content;
	if (prompt->cursor_position > 0)
	{
		ft_lstdel_at(&prompt->chars, prompt->cursor_position, &free_char);
		shell_prompt_display(sh);
	}
	return (READING);
}

enum e_prompt_status prompt_insert_char(char *buf)
{
	t_prompt	*prompt;
	t_sh		*sh;

	sh = shell_recover();
	prompt = sh->history->content;
	if (buf[0] && !(buf[1]) && !(buf[2]))
	{
		ft_lstadd_at(&prompt->chars, ft_lstnew(&buf[0], sizeof(char)), prompt->cursor_position);
		prompt->cursor_position++;
		shell_prompt_display(sh);
	}
	return (READING);
}

enum e_prompt_status prompt_fire_cmd(char *buf)
{
	if (!ENTER)
		return (TRYING);
	tputs(tgetstr("do", NULL), 0, tputs_putchar);
	return (FIRE_CMD);
}

static void	*shell_prompt_get_functions(void)
{
	static enum e_prompt_status	(*f[])(char *) = {
		prompt_move_right,
		prompt_move_left,
		prompt_delete_char,
		prompt_delete_next_char,
		prompt_fire_cmd,
		prompt_insert_char,
		NULL
	};

	return ((void *)f);
}

enum e_prompt_status	shell_prompt_boot_function(char *buf)
{
	enum e_prompt_status	(**functions)(char *);
	enum e_prompt_status 	status;

	functions = shell_prompt_get_functions();
	status = TRYING;
	while (*functions && status == TRYING)
	{
		status = (*functions)(buf);
		functions++;
	}
	return (status);
}

char 		*shell_prompt_get_command(t_prompt *prompt)
{
	char	*cmd;
	t_list	*cur;
	int 	i = 0;

	cmd = malloc(sizeof(char) * (ft_lstcount(prompt->chars) + 1));
	cur = prompt->chars;
	while (cur)
	{
		cmd[i] = *(char *)cur->content;
		cur = cur->next;
		i++;
	}
	cmd[i] = '\0';
	return (cmd);
}

char		*shell_prompt_input(t_sh *sh)
{
	char					buf[3];
	enum e_prompt_status	status;

	ft_bzero(buf, 3);
	UNUSED(sh);
	while (read(0, buf, 3))
	{
		status = shell_prompt_boot_function(buf);
		ft_bzero(buf, 3);
		if (status == FIRE_CMD)
			return (shell_prompt_get_command(sh->history->content));
	}
	return ("");
}