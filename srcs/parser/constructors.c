/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

t_cmd	*shell_parser_new_exec_cmd(void)
{
	t_exec_cmd *cmd;

	cmd = malloc(sizeof(*cmd));
	cmd->type = EXEC;
	return (t_cmd*)cmd;
}

t_cmd	*shell_parser_new_redirection_cmd(
	t_cmd *subcmd, char *file, int mode, int fd)
{
	t_redirection_cmd *cmd;

	cmd = malloc(sizeof(*cmd));
	cmd->type = REDIRECTION;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->mode = mode;
	cmd->fd = fd;
	return (t_cmd *)cmd;
}

t_cmd	*shell_parser_new_pipe_cmd(t_cmd *left, t_cmd *right)
{
	t_pipe_cmd *cmd;

	cmd = malloc(sizeof(*cmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return (t_cmd *)cmd;
}
