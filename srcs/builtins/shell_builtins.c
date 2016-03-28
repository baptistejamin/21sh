/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static t_builtin	*shell_builtins_get(void)
{
	static t_builtin	f[] = {
		{"pwd", shell_builtins_pwd},
		{"exit", shell_builtins_exit},
		{"cd", shell_builtins_cd},
		{"env", shell_builtins_env},
		{"setenv", shell_builtins_setenv},
		{"unsetenv", shell_builtins_unsetenv},
		{"help", shell_builtins_help},
		{NULL, shell_builtins_exit},
	};

	return ((void *)f);
}

int					shell_boot_builtin(t_sh *sh, t_list *environ, char **cmds)
{
	int			i;
	t_builtin	*builtins;

	i = 0;
	builtins = shell_builtins_get();
	while (builtins[i].name != NULL)
	{
		if (ft_strcmp(builtins[i].name, cmds[0]) == 0)
			return (builtins[i].func(sh, environ, cmds));
		i++;
	}
	return (0);
}

int					shell_is_builtin(t_sh *sh, char **cmds)
{
	int			i;
	t_builtin	*builtins;

	i = 0;
	builtins = shell_builtins_get();
	UNUSED(sh);
	while (builtins[i].name != NULL)
	{
		if (ft_strcmp(builtins[i].name, cmds[0]) == 0)
			return (1);
		i++;
	}
	return (0);
}
