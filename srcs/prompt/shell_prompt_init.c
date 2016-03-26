/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_prompt_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int			tputs_putchar(int c)
{
	t_sh	*sh;

	sh = shell_recover();
	write(sh->tty, &c, 1);
	return (1);
}

int		shell_prompt_init(t_sh *sh)
{ 
	char	buff_env[4096];

	if ((sh->term_name = getenv("TERM")) == NULL)
		return (0);
	if (tgetent(buff_env, sh->term_name) != 1)
		return (0);
	if (tcgetattr(0, &sh->term) == -1)
		return (0);
	sh->tty = 1;

	sh->term.c_lflag &= ~(ICANON | ECHO);
	sh->term.c_cc[VMIN] = 1;
	sh->term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &sh->term) == -1)
		return (0);
	tputs(tgetstr("te", NULL), 1, tputs_putchar);
	tputs(tgetstr("ve", NULL), 1, tputs_putchar);
	return (1);
}
