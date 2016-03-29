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

static void		shell_prompt_update_cursor_to_start(t_sh *sh)
{
	t_list		*char_list;
	int			printed_chars;
	int 		i;


	i = 0;
	char_list = sh->current_prompt->chars;
	tputs(tgetstr("cr", NULL), 0, tputs_putchar);
	printed_chars = 2;
	while (i < sh->current_prompt->lenght)
	{
		if (printed_chars >= sh->win.ws_col)
		{
			tputs(tgetstr("up", NULL), 0, tputs_putchar);
			tputs(tgetstr("cr", NULL), 0, tputs_putchar);
			printed_chars = 0;
		}
		printed_chars++;
		i++;
	}
}

int		shell_prompt_display(t_sh *sh, int show_cursor)
{
	int			i;
	t_list		*char_list;
	char		current_char;
	int			printed_chars;

	tputs(tgetstr("vi", NULL), 0, tputs_putchar);
	shell_prompt_update_cursor_to_start(sh);
	tputs(tgetstr("cd", NULL), 0, tputs_putchar);
	ft_putstr_fd("$>", sh->tty);
	printed_chars = shell_prompt_get_lenght();
	char_list =  sh->current_prompt->chars;
	i = 0;
	while (char_list)
	{
		tputs(tgetstr("me", NULL), 0, tputs_putchar);
		current_char = *(char *)char_list->content;
		if (i == sh->current_prompt->cursor_index && show_cursor)
			tputs(tgetstr("mr", NULL), 0, tputs_putchar);
		if (current_char)
			tputs_putchar(current_char);
		printed_chars++;
		if (printed_chars >= sh->win.ws_col)
		{
			ft_putendl("");
			tputs(tgetstr("cr", NULL), 0, tputs_putchar);
			printed_chars = 0;
		}
		i++;
		char_list = char_list->next;
	}
	if (i == sh->current_prompt->cursor_index && show_cursor)
	{
		tputs(tgetstr("mr", NULL), 0, tputs_putchar);
		tputs_putchar(' ');
	}
	tputs(tgetstr("me", NULL), 0, tputs_putchar);
	return (1);
}
