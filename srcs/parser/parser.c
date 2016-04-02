/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/02 21:26:27 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

t_cmd		*shell_parser_redirection(t_cmd *cmd, char **p, char *end)
{
	int		tok;
	char	*q;
	char	*eq;
	char	*f;

	while (shell_parser_helper_strings_whitespaces(p, end, "12<>"))
	{
		if ((**p == '1' || **p == '2') && (*p)[1] != '>' && (*p)[1] != '<')
			break ;
		tok = tokenizer(p, end, 0, 0);
		tokenizer(p, end, &q, &eq);
		if ((f = ft_strndup(q, eq - q + 1)) && tok == '<')
			cmd = shell_parser_new_redirection_cmd(cmd, f, M_READ, 0);
		if (tok == '>')
			cmd = shell_parser_new_redirection_cmd(cmd, f, M_WRITE_TRUNC, 1);
		if (tok == '+')
			cmd = shell_parser_new_redirection_cmd(cmd, f, M_WRITE_APPEND, 1);
		if (tok == '=')
			cmd = shell_parser_new_redirection_cmd(cmd, f, M_READ_APPEND, 0);
		if (tok == '*')
			cmd = shell_parser_new_redirection_cmd(cmd, f, M_WRITE_TRUNC, 2);
		if (tok == '/')
			cmd = shell_parser_new_redirection_cmd(cmd, f, M_WRITE_APPEND, 2);
	}
	return (cmd);
}

t_cmd		*shell_parser_exec(char **p_input, char *end, int *res)
{
	char			*new_cmd;
	char			*new_cmd_end;
	int				tok;
	t_exec_cmd		*cmd;
	t_cmd			*ret;

	ret = shell_parser_new_exec_cmd();
	cmd = (t_exec_cmd *)ret;
	cmd->argv = NULL;
	ret = shell_parser_redirection(ret, p_input, end);
	while (*p_input < end)
	{
		if ((tok = tokenizer(p_input, end, &new_cmd, &new_cmd_end)) == 0)
			break ;
		if (tok != 'a' && (*res = 0))
			return (NULL);
		ft_lstadd_back(&cmd->argv, ft_lstnew(
			ft_strndup(new_cmd, new_cmd_end - new_cmd),
			new_cmd_end - new_cmd + 1));
		ret = shell_parser_redirection(ret, p_input, end);
	}
	return (ret);
}

t_cmd		*shell_parser_pipe(char **p_input, char *end, int *res)
{
	t_cmd	*cmd;
	char	*new_cmd;
	char	*new_cmd_end;

	if (shell_parser_helper_strings_scan_pipes(
		p_input, end, &new_cmd, &new_cmd_end))
	{
		cmd = shell_parser_exec(&new_cmd, new_cmd_end, res);
		(*p_input)++;
		cmd = shell_parser_new_pipe_cmd(
			cmd, shell_parser_pipe(p_input, end, res));
	}
	else
		cmd = shell_parser_exec(&new_cmd, new_cmd_end, res);
	return (cmd);
}

t_cmd		*shell_parser(char *input)
{
	char		*end;
	t_cmd		*cmd;
	int			res;

	res = 1;
	end = input + ft_strlen(input);
	cmd = shell_parser_pipe(&input, end, &res);
	if (input != end || res == 0)
	{
		ft_putendl_fd("Syntax error", 2);
		return (NULL);
	}
	else
		return (cmd);
}
