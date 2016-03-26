/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_builtins_helpers_options_parser.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:13:52 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/12 21:20:26 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static t_generic_options	parse_options_init(void)
{
	t_generic_options	options;

	options.start = 1;
	options.error = 0;
	options.options_counter = 0;
	options.options[0] = 0;
	return (options);
}

static int					parse_options_helper(t_generic_options *options,
								char *managed_options, char option)
{
	int	res;

	if (ft_is_in(managed_options, option))
	{
		options->options[options->options_counter] = option;
		options->options_counter++;
		res = 1;
	}
	else
	{
		options->error = 1;
		options->error_char = option;
		res = 0;
	}
	options->options[options->options_counter] = 0;
	return (res);
}

t_generic_options			shell_builtins_options_parser(char **cmds,
								char *managed_options)
{
	t_generic_options	options;
	int					i;
	int					n;

	i = 1;
	options = parse_options_init();
	while (cmds[i] && cmds[i][0] == '-')
	{
		n = 1;
		if (ft_strcmp(cmds[i], "--") == 0)
		{
			options.start++;
			return (options);
		}
		while (cmds[i][n])
		{
			if (!parse_options_helper(&options, managed_options, cmds[i][n]))
				return (options);
			n++;
		}
		options.start = ++i;
	}
	return (options);
}
