/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_builtins_help.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int		shell_builtins_help(void *sh_, t_list *environ, char **cmds)
{
	UNUSED(sh_);
	UNUSED(cmds);
	UNUSED(environ);
	ft_putendl("help:\n");
	ft_putendl("builtins:");
	ft_putendl("cd [-LP] [path]");
	ft_putendl("pwd [-LP]");
	ft_putendl("exit [code]");
	ft_putendl("env [-i] [var=value, ...] [cmd]");
	ft_putendl("setenv [var] [value]");
	ft_putendl("unsetenv [var]");
	return (0);
}
