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

enum e_prompt_status prompt_move_next_word(char *buf)
{
	t_sh		*sh;
	t_list		*cur;

	sh = shell_recover();
	if (!SHIFT_RIGHT)
		return (TRYING);
	while (sh->current_prompt->cursor_index < sh->current_prompt->lenght)
	{
		cur = ft_lstget_at(sh->current_prompt->chars, sh->current_prompt->cursor_index);
		if (cur && !ft_isspace(*(char *)cur->content))
			sh->current_prompt->cursor_index++;
		else
			break;
	}
	while (sh->current_prompt->cursor_index < sh->current_prompt->lenght)
	{
		cur = ft_lstget_at(sh->current_prompt->chars, sh->current_prompt->cursor_index);
		if (cur && ft_isspace(*(char *)cur->content))
			sh->current_prompt->cursor_index++;
		else
			break;
	}
	shell_prompt_display(sh,1 );
	return (READING);
}

enum e_prompt_status prompt_move_last_word(char *buf)
{
	t_sh		*sh;
	t_list		*cur;

	sh = shell_recover();
	if (!SHIFT_LEFT)
		return (TRYING);
	while (sh->current_prompt->cursor_index > 0)
	{
		cur = ft_lstget_at(sh->current_prompt->chars, sh->current_prompt->cursor_index - 1);
		if (cur && ft_isspace(*(char *)cur->content))
			sh->current_prompt->cursor_index--;
		else
			break;
	}
	while (sh->current_prompt->cursor_index > 0)
	{
		cur = ft_lstget_at(sh->current_prompt->chars, sh->current_prompt->cursor_index - 1);
		if (cur && !ft_isspace(*(char *)cur->content))
			sh->current_prompt->cursor_index--;
		else
			break;
	}
	shell_prompt_display(sh,1 );
	return (READING);
}

enum e_prompt_status prompt_move_up(char *buf)
{
	t_sh		*sh;

	sh = shell_recover();
	if (!SHIFT_UP)
		return (TRYING);
	if (sh->current_prompt->cursor_index - sh->win.ws_col >= 0)
		sh->current_prompt->cursor_index -= sh->win.ws_col;
	else
		sh->current_prompt->cursor_index = 0;
	shell_prompt_display(sh,1 );;
	return (READING);
}

enum e_prompt_status prompt_move_down(char *buf)
{
	t_sh		*sh;

	sh = shell_recover();
	if (!SHIFT_DOWN)
		return (TRYING);
	if (sh->current_prompt->cursor_index + sh->win.ws_col <= sh->current_prompt->lenght)
		sh->current_prompt->cursor_index += sh->win.ws_col;
	else
		sh->current_prompt->cursor_index = sh->current_prompt->lenght;
	shell_prompt_display(sh,1 );;
	return (READING);
}


enum e_prompt_status prompt_move_right(char *buf)
{
	t_sh		*sh;

	sh = shell_recover();
	if (!RIGHT)
		return (TRYING);
	if (sh->current_prompt->cursor_index < sh->current_prompt->lenght)
	{
		sh->current_prompt->cursor_index++;
		shell_prompt_display(sh,1 );
	}
	else
		tputs(tgetstr("bl", NULL), 0, tputs_putchar);
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
		shell_prompt_display(sh, 1);
	}
	else
		tputs(tgetstr("bl", NULL), 0, tputs_putchar);
	return (READING);
}

enum e_prompt_status prompt_move_start(char *buf)
{
	t_sh		*sh;

	sh = shell_recover();
	if (!HOME)
		return (TRYING);
	sh->current_prompt->cursor_index = 0;
	shell_prompt_display(sh, 1);
	return (READING);
}

enum e_prompt_status prompt_move_end(char *buf)
{
	t_sh		*sh;

	sh = shell_recover();
	if (!END)
		return (TRYING);
	sh->current_prompt->cursor_index = sh->current_prompt->lenght;
	shell_prompt_display(sh, 1);
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
		sh->current_prompt->lenght--;
		shell_prompt_display(sh, 1);
	}
	else
		tputs(tgetstr("bl", NULL), 0, tputs_putchar);
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
		sh->current_prompt->lenght--;
		shell_prompt_display(sh, 1);
	}
	else
		tputs(tgetstr("bl", NULL), 0, tputs_putchar);
	return (READING);
}

void	 prompt_insert_one_char(char car)
{
	t_sh		*sh;

	sh = shell_recover();
	ft_lstadd_at(&sh->current_prompt->chars, ft_lstnew(&car, sizeof(char)), sh->current_prompt->cursor_index);
	sh->current_prompt->cursor_index++;
	sh->current_prompt->lenght++;
}

enum e_prompt_status prompt_insert_char(char *buf)
{
	t_sh		*sh;

	sh = shell_recover();
	if (buf[0])
		prompt_insert_one_char(buf[0]);
	if (buf[1])
		prompt_insert_one_char(buf[1]);
	if (buf[2])
		prompt_insert_one_char(buf[2]);
	shell_prompt_display(sh, 1);
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
		shell_prompt_display(sh, 1);
	}
	else
		tputs(tgetstr("bl", NULL), 0, tputs_putchar);
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
		shell_prompt_display(sh, 1);
	}
	else
		tputs(tgetstr("bl", NULL), 0, tputs_putchar);
	return (READING);
}

enum e_prompt_status prompt_autocompletion(char *buf)
{
	t_sh		*sh;
	t_list		*cur;
	char		*search;
	int			start_position;
	char 		*result;

	sh = shell_recover();
	if (!TAB)
		return (TRYING);
	while (sh->current_prompt->cursor_index > 0 && 
		sh->current_prompt->cursor_index < sh->current_prompt->lenght)
	{
		cur = ft_lstget_at(sh->current_prompt->chars, sh->current_prompt->cursor_index);
		if (cur && !ft_isspace(*(char *)cur->content))
			sh->current_prompt->cursor_index++;
		else
			break;
	}
	start_position = sh->current_prompt->cursor_index;
	while (start_position > 0)
	{
		cur = ft_lstget_at(sh->current_prompt->chars, start_position - 1);
		if (cur && !ft_isspace(*(char *)cur->content))
			start_position--;
		else
			break;
	}
	search = shell_prompt_get_command(sh->current_prompt, start_position, sh->current_prompt->cursor_index);
	result =  shell_prompt_autocompletion(search);
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
	shell_prompt_display(sh, 1);
	return (READING);
}

enum e_prompt_status prompt_fire_cmd(char *buf)
{
	t_sh		*sh;

	sh = shell_recover();
	if (!ENTER)
		return (TRYING);
	shell_prompt_display(sh, 0);
	tputs(tgetstr("do", NULL), 0, tputs_putchar);
	return (FIRE_CMD);
}

static void	*shell_prompt_get_functions(void)
{
	static enum e_prompt_status	(*f[])(char *) = {
		prompt_move_next_word,
		prompt_move_last_word,
		prompt_move_up,
		prompt_move_down,
		prompt_move_right,
		prompt_move_left,
		prompt_move_start,
		prompt_move_end,
		prompt_delete_char,
		prompt_delete_next_char,
		prompt_fire_cmd,
		prompt_move_to_last_prompt,
		prompt_move_to_next_prompt,
		prompt_autocompletion,
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

char 		*shell_prompt_get_command(t_prompt *prompt, size_t start, size_t end)
{
	char	*cmd;
	t_list	*cur;
	size_t 	i; 

	i = 0;
	cmd = malloc(sizeof(char) * ((end - start) + 1));
	cur = ft_lstget_at(prompt->chars, start);
	while (cur && i < (end - start))
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
		//printf("\n\n%s %s %s %c %c %c", ft_itoa(buf[0]), ft_itoa(buf[1]), ft_itoa(buf[2]), buf[0], buf[1], buf[2]);
		status = shell_prompt_boot_function(buf);
		ft_bzero(buf, 3);
		if (status == FIRE_CMD)
			return (shell_prompt_get_command(sh->current_prompt, 0, sh->current_prompt->lenght));
	}
	return ("");
}