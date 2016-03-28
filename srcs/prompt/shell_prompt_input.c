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

	sh = shell_recover();
	if (!RIGHT)
		return (TRYING);
	if (sh->current_prompt->cursor_index < ft_lstcount(sh->current_prompt->chars))
	{
		sh->current_prompt->cursor_index++;
		shell_prompt_display(sh);
	}
	return (READING);
}

enum e_prompt_status prompt_move_left(char *buf)
{
	t_sh		*sh;

	sh = shell_recover();
	if (!LEFT)
		return (TRYING);
	if (sh->current_prompt->cursor_index > 0)
	{
		sh->current_prompt->cursor_index--;
		shell_prompt_display(sh);
	}
	return (READING);
}

enum e_prompt_status prompt_delete_char(char *buf)
{
	t_sh		*sh;

	sh = shell_recover();
	if (!BACK_SPACE)
		return (TRYING);
	if (sh->current_prompt->cursor_index > 0)
	{
		ft_lstdel_at(&sh->current_prompt->chars, sh->current_prompt->cursor_index - 1, &free_char);
		sh->current_prompt->cursor_index--;
		shell_prompt_display(sh);
	}
	return (READING);
}

enum e_prompt_status prompt_delete_next_char(char *buf)
{
	t_sh		*sh;

	sh = shell_recover();
	if (!DELETE)
		return (TRYING);
	if (sh->current_prompt->cursor_index > 0)
	{
		ft_lstdel_at(&sh->current_prompt->chars, sh->current_prompt->cursor_index, &free_char);
		shell_prompt_display(sh);
	}
	return (READING);
}

enum e_prompt_status prompt_insert_char(char *buf)
{
	t_sh		*sh;

	sh = shell_recover();
	if (buf[0] && !(buf[1]) && !(buf[2]))
	{
		ft_lstadd_at(&sh->current_prompt->chars, ft_lstnew(&buf[0], sizeof(char)), sh->current_prompt->cursor_index);
		sh->current_prompt->cursor_index++;
		shell_prompt_display(sh);
	}
	return (READING);
}

enum e_prompt_status prompt_move_to_last_prompt(char *buf)
{
	t_sh		*sh;

	sh = shell_recover();
	if (!UP)
		return (TRYING);
	if (ft_lstget_at(sh->history, sh->prompt_position + 1))
	{
		sh->prompt_position++;
		sh->current_prompt = ft_lstget_at(sh->history, sh->prompt_position)->content;
		shell_prompt_display(sh);
	}
	return (READING);
}

enum e_prompt_status prompt_move_to_next_prompt(char *buf)
{
	t_sh		*sh;

	sh = shell_recover();
	if (!DOWN)
		return (TRYING);
	if (ft_lstget_at(sh->history, sh->prompt_position - 1))
	{
		sh->prompt_position--;
		sh->current_prompt = ft_lstget_at(sh->history, sh->prompt_position)->content;
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
		prompt_move_to_last_prompt,
		prompt_move_to_next_prompt,
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
		//printf("\n%s %s %s", ft_itoa(buf[0]), ft_itoa(buf[1]), ft_itoa(buf[2]));
		status = shell_prompt_boot_function(buf);
		ft_bzero(buf, 3);
		if (status == FIRE_CMD)
			return (shell_prompt_get_command(sh->current_prompt));
	}
	return ("");
}