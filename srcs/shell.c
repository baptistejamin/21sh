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

#include <prompt.h>
#include <shell.h>

t_sh			*shell_recover(void)
{
	static t_sh	sh;

	return (&sh);
}

static int		shell_fire_cmds(char *input)
{
	t_cmd	*cmd;
	char	**inputs;
	int		i;
	int		ret;

	i = 0;
	ret = 1;
	inputs = ft_strsplit(input, ';');
	while (inputs[i])
	{
		cmd = shell_parser(inputs[i]);
		if (cmd)
			shell_exec(cmd);
		else
			ret = 0;
		i++;
	}
	if (inputs[0])
		ft_free_tab(inputs);
	return (ret);
}

static int		shell(t_sh *sh)
{
	char	*input;
	int		is_last_cmd_empty;

	UNUSED(sh);
	is_last_cmd_empty = 0;
	while (1)
	{
		shell_prompt_init();
		if (!is_last_cmd_empty)
			shell_prompt_add_new();
		shell_prompt_display(1);
		input = shell_prompt_input();
		if (input)
		{
			shell_prompt_reset();
			is_last_cmd_empty = !shell_fire_cmds(input);
			free(input);
		}
	}
	return (0);
}

static void		show_welcome(t_sh *sh)
{
	int		fd;
	char	*line;

	UNUSED(sh);
	fd = open(".banner", O_RDWR);
	while (get_next_line(fd, &line))
		ft_putendl(line);
	close(fd);
}

int				main(int argc, char **argv, char **environ)
{
	t_sh	*sh;
	char	*nb;

	UNUSED(argv);
	sh = shell_recover();
	sh->tty = open("/dev/tty", O_RDWR);
	if (argc > 1)
	{
		ft_putendl_fd("21sh cannot execute commands", 2);
		return (0);
	}
	show_welcome(sh);
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
