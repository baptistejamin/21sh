/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_builtins_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static int	shell_builtins_env_set_vars(t_generic_options *options,
											t_list **list, char **cmds)
{
	int		i;
	char	*var;
	char	*value;

	i = options->start;
	while (cmds[i])
	{
		if (ft_strchr(cmds[i], '='))
		{
			var = ft_strnew(ft_strlen(cmds[i]) -
			ft_strlen(ft_strchr(cmds[i], '=') + 1));
			ft_strncpy(var, cmds[i], ft_strlen(cmds[i]) -
			ft_strlen(ft_strchr(cmds[i], '=')));
			value = ft_strdup(ft_strchr(cmds[i], '=') + 1);
			shell_builtins_setenv_set(list, var, value);
			free(var);
			free(value);
		}
		else
			return (i);
		i++;
	}
	return (i);
}

static void	ft_envcpy(t_list **dest, t_list *src)
{
	t_env	new_env;
	t_env	*env;

	while (src)
	{
		env = src->content;
		new_env.var = ft_strdup(env->var);
		new_env.value = ft_strdup(env->value);
		ft_lstadd(dest, ft_lstnew(&new_env, src->content_size));
		src = src->next;
	}
}

int			shell_builtins_env(void *sh_, t_list *environ, char **cmds)
{
	t_sh				*sh;
	t_generic_options	options;
	t_list				*new_env;
	int					cmd_index;

	sh = (t_sh *)sh_;
	options = shell_builtins_options_parser(cmds, "i");
	if (options.error)
	{
		ft_putstr_fd("env: illegal option -- ", 2);
		ft_putchar_fd(options.error_char, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	new_env = NULL;
	if (!ft_is_in(options.options, 'i'))
		ft_envcpy(&new_env, environ);
	cmd_index = shell_builtins_env_set_vars(&options, &new_env, cmds);
	if (!cmds[cmd_index])
		shell_env_show(new_env);
	else
		shell_boot(sh, new_env, &cmds[cmd_index]);
	if (new_env)
		ft_lstdel(&new_env, &shell_builtins_unsetenv_free);
	return (0);
}
