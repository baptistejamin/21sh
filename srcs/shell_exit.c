/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void	shell_exit(void)
{
	t_sh *sh;

	sh = shell_recover();
	if (sh->env_list)
	{
		ft_lstdel(&sh->env_list, &shell_builtins_unsetenv_free);
		free(sh->env_list);
	}
	shell_prompt_reset();
	exit(sh->last_res);
}