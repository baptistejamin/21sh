/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_prompt_display.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <stdio.h>

int		tputs_putchar(int c)
{
	t_sh	*sh;

	sh = shell_recover();
	write(sh->tty, &c, 1);
	return (1);
}

static int		shell_prompt_get_lenght(void)
{
	return (2);
}

static int		shell_prompt_get_lines(void)
{
	int 	chars;
	t_sh	*sh;

	sh = shell_recover();
	chars  = shell_prompt_get_lenght() + ft_lstcount(sh->current_prompt->chars);
	return (chars / (sh->win.ws_col) + 1);
}

static void		shell_prompt_update_cursor(t_sh *sh, int position)
{
	t_list		*char_list;
	int			i;

	char_list = sh->current_prompt->chars;
	tputs(tgetstr("cr", NULL), 0, tputs_putchar);
	i = 0;
	while (i < (shell_prompt_get_lines() - 1))
	{
		tputs(tgetstr("up", NULL), 0, tputs_putchar);
		tputs(tgetstr("cr", NULL), 0, tputs_putchar);
		tputs(tgetstr("cd", NULL), 0, tputs_putchar);
		i++;
	}
	/*position -= (shell_prompt_get_lines() - 1) *  sh->win.ws_col;
	while (position > 0)
	{
		tputs(tgetstr("nd", NULL), 0, tputs_putchar);
		position--;
	}*/
}

int		shell_prompt_display(t_sh *sh)
{
	t_list		*char_list;
	char		current_char;
	int			printed_chars;

	tputs(tgetstr("cd", NULL), 0, tputs_putchar);
	shell_prompt_update_cursor(sh, 0);
	ft_putstr_fd("$>", sh->tty);
	printed_chars = shell_prompt_get_lenght();
	char_list =  sh->current_prompt->chars;
	while (char_list)
	{
		current_char = *(char *)char_list->content;
		printed_chars++;
		if (printed_chars > sh->win.ws_col)
		{
			ft_putendl("");
			tputs(tgetstr("cr", NULL), 0, tputs_putchar);
			tputs(tgetstr("cd", NULL), 0, tputs_putchar);
			printed_chars = 0;
		}
		if (current_char)
			tputs_putchar(current_char);
		char_list = char_list->next;
	}
	//shell_prompt_update_cursor(sh, shell_prompt_get_lenght() + sh->current_prompt->cursor_index);
	return (1);
}
