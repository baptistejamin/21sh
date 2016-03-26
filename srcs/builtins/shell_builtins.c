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

void	shell_init_builtin(t_builtin *buitin, char *name, t_func func)
{
	buitin->name = name;
	buitin->func = func;
}

void	shell_init_builtins(t_sh *sh)
{
	shell_init_builtin(&sh->builtins[0], "pwd", &shell_builtins_pwd);
	shell_init_builtin(&sh->builtins[1], "exit", &shell_builtins_exit);
	shell_init_builtin(&sh->builtins[2], "cd", &shell_builtins_cd);
	shell_init_builtin(&sh->builtins[3], "env", &shell_builtins_env);
	shell_init_builtin(&sh->builtins[4], "setenv",
		&shell_builtins_setenv);
	shell_init_builtin(&sh->builtins[5], "unsetenv",
		&shell_builtins_unsetenv);
	shell_init_builtin(&sh->builtins[6], "help",
		&shell_builtins_help);
	shell_init_builtin(&sh->builtins[7], "", &shell_builtins_exit);
}

int		shell_boot_builtin(t_sh *sh, t_list *environ, char **cmds)
{
	int i;

	i = 0;
	while (sh->builtins[i].name[0] != '\0')
	{
		if (ft_strcmp(sh->builtins[i].name, cmds[0]) == 0)
			return (sh->builtins[i].func(sh, environ, cmds));
		i++;
	}
	return (0);
}

int		shell_is_builtin(t_sh *sh, char **cmds)
{
	int i;

	i = 0;
	while (sh->builtins[i].name[0] != '\0')
	{
		if (ft_strcmp(sh->builtins[i].name, cmds[0]) == 0)
			return (1);
		i++;
	}
	return (0);
}
