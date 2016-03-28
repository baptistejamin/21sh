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

void	shell_prompt_add_new(t_sh *sh)
{
	t_prompt	prompt;

	prompt.chars = NULL;
	prompt.cursor_position = 0;
	ft_lstadd(&sh->history, ft_lstnew(&prompt, sizeof(t_prompt)));
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
	return (1);
}
