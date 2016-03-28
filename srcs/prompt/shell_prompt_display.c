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

int		tputs_putchar(int c)
{
	t_sh	*sh;

	sh = shell_recover();
	write(sh->tty, &c, 1);
	return (1);
}

static void		shell_prompt_update_cursor(void)
{
	t_sh		*sh;
	int			i;

	sh = shell_recover();
	i = 0;
	tputs(tgetstr("cr", NULL), 0, tputs_putchar);

	//Prompt len
	tputs(tgetstr("nd", NULL), 0, tputs_putchar);
	tputs(tgetstr("nd", NULL), 0, tputs_putchar);
	while (i < sh->current_prompt->cursor_index)
	{
		tputs(tgetstr("nd", NULL), 0, tputs_putchar);
		i++;
	}

}

int		shell_prompt_display(t_sh *sh)
{
	t_list		*char_list;
	char		current_char;

	tputs(tgetstr("cr", NULL), 0, tputs_putchar);
	tputs(tgetstr("ce", NULL), 0, tputs_putchar);
	ft_putstr_fd("$>", sh->tty);
	char_list =  sh->current_prompt->chars;
	while (char_list)
	{
		current_char = *(char *)char_list->content;
		if (current_char)
			tputs_putchar(current_char);
		char_list = char_list->next;
	}
	shell_prompt_update_cursor();
	return (1);
}
