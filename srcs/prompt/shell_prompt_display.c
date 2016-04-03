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

int				tputs_putchar(int c)
{
	t_sh	*sh;

	sh = shell_recover();
	write(sh->tty, &c, 1);
	return (1);
}

static int		shell_prompt_get_lenght(void)
{
	return (7);
}

static void		shell_prompt_update_cursor_to_start(t_sh *sh)
{
	t_list	*char_list;
	int		printed_chars;
	int		i;

	i = 0;
	char_list = sh->c_prompt->chars;
	tputs(tgetstr("cr", NULL), 0, tputs_putchar);
	printed_chars = shell_prompt_get_lenght();
	while (i < sh->c_prompt->lenght)
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

static void		shell_prompt_display_chars(
	t_list *cur, int show_cursor, int *i, int *printed_chars)
{
	char	current_char;
	t_sh	*sh;

	sh = shell_recover();
	tputs(tgetstr("me", NULL), 0, tputs_putchar);
	tputs(tgetstr("ue", NULL), 0, tputs_putchar);
	current_char = *(char *)cur->content;
	if (*i == sh->c_prompt->cursor_index && show_cursor)
		tputs(tgetstr("mr", NULL), 0, tputs_putchar);
	if (sh->c_prompt->copy_mode && show_cursor &&
		*i >= sh->c_prompt->copy_start && *i <= sh->c_prompt->copy_end)
		tputs(tgetstr("us", NULL), 0, tputs_putchar);
	if (current_char)
		tputs_putchar(current_char);
	(*printed_chars)++;
	if (*printed_chars >= sh->win.ws_col)
	{
		ft_putendl("");
		tputs(tgetstr("cr", NULL), 0, tputs_putchar);
		*printed_chars = 0;
	}
	(*i)++;
}

void			shell_prompt_display(int show_cursor)
{
	int		i;
	t_list	*char_list;
	int		printed_chars;
	t_sh	*sh;

	sh = shell_recover();
	tputs(tgetstr("vi", NULL), 0, tputs_putchar);
	shell_prompt_update_cursor_to_start(sh);
	tputs(tgetstr("cd", NULL), 0, tputs_putchar);
	ft_putstr_fd("21sh $>", sh->tty);
	printed_chars = shell_prompt_get_lenght();
	char_list = sh->c_prompt->chars;
	i = 0;
	while (char_list)
	{
		shell_prompt_display_chars(char_list, show_cursor, &i, &printed_chars);
		char_list = char_list->next;
	}
	if (i == sh->c_prompt->cursor_index && show_cursor)
	{
		tputs(tgetstr("mr", NULL), 0, tputs_putchar);
		tputs_putchar(' ');
	}
	tputs(tgetstr("me", NULL), 0, tputs_putchar);
	tputs(tgetstr("ue", NULL), 0, tputs_putchar);
}
