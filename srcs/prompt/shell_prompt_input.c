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

static void				*shell_prompt_get_functions(void)
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
		prompt_ignore_input,
		prompt_shell_quit,
		prompt_insert_char,
		NULL
	};

	return ((void *)f);
}

enum e_prompt_status	shell_prompt_boot_function(char *buf)
{
	enum e_prompt_status	(**functions)(char *);
	enum e_prompt_status	status;

	functions = shell_prompt_get_functions();
	status = TRYING;
	while (*functions && status == TRYING)
	{
		status = (*functions)(buf);
		functions++;
	}
	return (status);
}

char					*shell_prompt_get_command(
	t_prompt *prompt, size_t start, size_t end)
{
	char	*cmd;
	t_list	*cur;
	size_t	i;

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

char					*shell_prompt_input(void)
{
	char					buf[3];
	enum e_prompt_status	status;
	t_sh					*sh;

	sh = shell_recover();
	ft_bzero(buf, 3);
	while (read(0, buf, 3))
	{
		status = shell_prompt_boot_function(buf);
		ft_bzero(buf, 3);
		if (status == FIRE_CMD)
			return (shell_prompt_get_command(
				sh->c_prompt, 0, sh->c_prompt->lenght));
	}
	return (NULL);
}
