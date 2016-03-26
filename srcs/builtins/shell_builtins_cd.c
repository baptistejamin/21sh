/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_builtins_cd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/20 13:40:16 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static int	cd_move_path(t_sh *sh, t_list *environ,
							t_generic_options *options, char *curpath)
{
	if (ft_is_in(options->options, 'P') && !ft_is_in(options->options, 'L'))
	{
		if (*curpath == '/')
			curpath = ft_strfjoin(ft_strjoin(
				shell_env_get(environ, "PWD"), "/"), curpath);
		return (shell_builtins_cd_change_directory(sh, &environ,
					curpath, 1));
	}
	else
		return (shell_builtins_cd_change_directory(sh, &environ,
					curpath, 0));
}

int			shell_builtins_cd(void *sh_, t_list *environ, char **cmds)
{
	t_generic_options	options;
	char				*directory;
	char				*curpath;
	t_sh				*sh;

	sh = (t_sh *)sh_;
	options = shell_builtins_options_parser(cmds, "LP");
	if (!cmds[options.start] && ft_strcmp(cmds[options.start - 1], "-") == 0)
		options.start--;
	directory = cmds[options.start];
	if (!directory || ft_strcmp(cmds[options.start], "~") == 0)
		directory = shell_builtins_cd_assert_home(sh, environ);
	if (!directory)
		return (shell_builtins_cd_error(0, ""));
	if (cmds[options.start] && ft_strcmp(cmds[options.start], "-") == 0)
		directory = shell_env_get(environ, "OLDPWD");
	if (cmds[options.start] && cmds[options.start + 1])
	{
		directory = shell_builtins_cd_assert_multiple_args(sh, cmds,
			&options);
		if (!directory)
			return (1);
	}
	curpath = directory;
	return (cd_move_path(sh, environ, &options, curpath));
}
