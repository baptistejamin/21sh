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

t_sh			*shell_recover(void)
{
	static t_sh	sh;

	return (&sh);
}

static int		shell(t_sh *sh)
{
	char *cmd;
	char **cmds;
	int	is_last_cmd_empty;

	is_last_cmd_empty = 0;
	shell_prompt_init(sh);
	while (1)
	{
		if (!is_last_cmd_empty)
			shell_prompt_add_new(sh);
		shell_prompt_display(sh);
		cmd = shell_prompt_input(sh);
		cmd = ft_strfjoin(cmd, " ");
		cmds = ft_str_to_tab(cmd);
		shell_boot(sh, sh->env_list, cmds);
		is_last_cmd_empty = (cmds[0] == 0);
		if (cmd)
			free(cmd);
		if (cmds)
			ft_free_tab(cmds);
		cmds = NULL;
	}
	return (0);
}

int				main(int argc, char **argv, char **environ)
{
	t_sh	*sh;
	char	*nb;

	sh = shell_recover();
	UNUSED(argv);
	if (argc > 1)
	{
		ft_putendl_fd("21sh cannot execute commands", 2);
		return (0);
	}
	sh->env_list = NULL;
	shell_env_to_list(&sh->env_list, environ);
	if (shell_env_get(sh->env_list, "SHLVL"))
		nb = ft_itoa(ft_atoi(shell_env_get(sh->env_list, "SHLVL")) + 1);
	else
		nb = ft_itoa(1);
	shell_builtins_setenv_set(&sh->env_list, "SHLVL", nb);
	if (nb)
		free(nb);
	shell_signals();
	return (shell(sh));
}
