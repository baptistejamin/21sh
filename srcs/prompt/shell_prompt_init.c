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

void	shell_prompt_add_new(void)
{
	t_sh		*sh;
	t_prompt	prompt;

	sh = shell_recover();
	prompt.chars = NULL;
	prompt.cursor_index = 0;
	prompt.copy_mode = 0;
	prompt.copy_start = 0;
	prompt.copy_end = 0;
	prompt.copy_word = NULL;
	prompt.lenght = 0;
	ft_lstadd(&sh->history, ft_lstnew(&prompt, sizeof(t_prompt)));
	sh->c_prompt = sh->history->content;
}

int		shell_prompt_init(void)
{
	char	buff_env[4096];
	t_sh	*sh;

	sh = shell_recover();
	if ((sh->term_name = getenv("TERM")) == NULL)
		return (0);
	if (tgetent(buff_env, sh->term_name) != 1)
		return (0);
	if (tcgetattr(0, &sh->term) == -1)
		return (0);
	if (tcgetattr(0, &sh->default_term))
		return (0);
	sh->signals_disabled = 0;
	sh->term.c_lflag &= ~(ICANON | ECHO);
	sh->term.c_cc[VMIN] = 1;
	sh->term.c_cc[VTIME] = 0;
	sh->prompt_position = 0;
	if (tcsetattr(0, TCSADRAIN, &sh->term) == -1)
		return (0);
	shell_prompt_update_window();
	return (1);
}

int		shell_prompt_update_window(void)
{
	t_sh *sh;

	sh = shell_recover();
	return (ioctl(0, TIOCGWINSZ, &sh->win) != -1);
}

int		shell_prompt_reset(void)
{
	t_sh *sh;

	sh = shell_recover();
	sh->term.c_lflag = (ICANON | ECHO | ISIG);
	sh->signals_disabled = 1;
	if (tcsetattr(0, TCSANOW, &sh->term) == -1)
		return (0);
	tputs(tgetstr("ve", NULL), 1, tputs_putchar);
	return (1);
}
