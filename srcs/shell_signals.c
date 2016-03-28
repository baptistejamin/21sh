/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static void	shell_signals_exit(int i)
{
	UNUSED(i);
	signal(SIGQUIT, SIG_DFL);
}

static	void	shell_signals_resize(int i)
{
	UNUSED(i);
	shell_prompt_update_window(shell_recover());
	shell_prompt_display(shell_recover());
}


static void	shell_signals_events(i)
{
	if (i == SIGWINCH)
		shell_signals_resize(i);
	else if (i == SIGINT)
		shell_signals_exit(i);
	else if (i == SIGQUIT)
		shell_signals_exit(i);
}

void	shell_signals(void)
{
	signal(SIGINT, shell_signals_events);
	signal(SIGWINCH, shell_signals_events);
}
