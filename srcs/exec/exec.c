/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <stdio.h>

void shell_exec_cmd(t_cmd *cmd)
{
	t_sh				*sh;
	t_list			*cur;
	t_exec_cmd	*ecmd;
	char				**argv;
	int					i;

	ecmd = (t_exec_cmd *)cmd;
	sh = shell_recover();
	argv = malloc(sizeof(char *) * (ft_lstcount(ecmd->argv) + 1));
	i = 0;
	cur = ecmd->argv;
	while (cur)
	{
		argv[i] = cur->content;
		i++;
		cur = cur->next;
	}
	argv[i] = NULL;
	sh->last_res = shell_boot(sh, sh->env_list, argv);
	sh->pid = 0;
}



void shell_exec_pipe(t_cmd *cmd)
{
	t_pipe_cmd	*pcmd;
	int 				pipes[2];
	int					pid1;
	int					pid2;
	t_sh				*sh;
	int					status;

	pcmd = (t_pipe_cmd *)cmd;
	if(pipe(pipes) != 0)
	{
		ft_putendl_fd("pipe error", 2);
		exit(0);
	}
	sh = shell_recover();
	if((pid1 = fork()) == 0)
	{
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[0]);
		shell_exec(pcmd->left);
		exit(0);
	}
	if((pid2 = fork()) == 0)
	{
		dup2(pipes[0], STDIN_FILENO);
		close(pipes[1]);
		shell_exec(pcmd->right);
		exit(0);
	}
	close(pipes[0]);
  close(pipes[1]);
  waitpid(-1, &status, 0);
  waitpid(-1, &status, 0);
  //waitpid(pid2, &status, 0);
}

void shell_exec_redirection(t_cmd *cmd)
{
	t_redirection_cmd	*rcmd;
	int new_fd;
	int	back_fd;

	rcmd = (t_redirection_cmd *)cmd;
		//close(rcmd->fd);
	new_fd = open(rcmd->file, rcmd->mode, S_IRUSR | S_IWUSR);
	back_fd = dup(rcmd->fd);
	dup2(new_fd, rcmd->fd);
	close(new_fd);
	shell_exec(rcmd->cmd);
	dup2(back_fd, rcmd->fd);
}

int shell_exec(t_cmd *cmd)
{
	int	ret;

	ret = 1;
	if (cmd->type == PIPE)
		shell_exec_pipe(cmd);
	else if (cmd->type == REDIRECTION)
		shell_exec_redirection(cmd);
	else if (cmd->type == EXEC)
		shell_exec_cmd(cmd);
	else
		ret = 0;
	return (ret);
}
