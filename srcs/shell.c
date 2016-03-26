/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static int		shell(t_sh *sh)
{
	char	**cmds;
	char	*cmd;
	int		res;

	res = 0;
	ft_putstr("$>");
	while (get_next_line(0, &cmd))
	{
		sh->last_res = res;
		cmd = ft_strfjoin(cmd, " ");
		cmds = ft_str_to_tab(cmd);
		res = shell_boot(sh, sh->env_list, cmds);
		if (cmd)
			free(cmd);
		if (cmds)
			ft_free_tab(cmds);
		cmds = NULL;
		ft_putstr("$>");
	}
	if (sh->env_list)
	{
		ft_lstdel(&sh->env_list, &shell_builtins_unsetenv_free);
		free(sh->env_list);
	}
	return (res);
}

int				main(int argc, char **argv, char **environ)
{
	t_sh	sh;
	char	*nb;

	UNUSED(argv);
	if (argc > 1)
	{
		ft_putendl_fd("shell cannot execute commands", 2);
		return (0);
	}
	shell_init_builtins(&sh);
	sh.env_list = NULL;
	shell_env_to_list(&sh.env_list, environ);
	if (shell_env_get(sh.env_list, "SHLVL"))
		nb = ft_itoa(ft_atoi(shell_env_get(sh.env_list, "SHLVL")) + 1);
	else
		nb = ft_itoa(1);
	shell_builtins_setenv_set(&sh.env_list, "SHLVL", nb);
	if (nb)
		free(nb);
	shell_signals();
	return (shell(&sh));
}
