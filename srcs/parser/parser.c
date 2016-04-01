/* ************************************************************************** */
/*																																						*/
/*																												:::		  ::::::::   */
/*   parser.c																				   :+:		  :+:		:+:   */
/*																										+:+ +:+				 +:+		 */
/*   By: bjamin <bjamin@student.42.fr>						  +#+  +:+		   +#+				*/
/*																								+#+#+#+#+#+   +#+				   */
/*   Created: 2016/03/10 14:06:11 by bjamin						#+#		#+#						 */
/*   Updated: 2016/03/15 13:10:37 by bjamin				   ###   ########.fr		   */
/*																																						*/
/* ************************************************************************** */

#include <shell.h>
#include <stdio.h>

t_cmd	*shell_parser_new_exec_cmd(void)
{
	t_exec_cmd *cmd;

	cmd = malloc(sizeof(*cmd));
	cmd->type = EXEC;
	return (t_cmd*)cmd;
}

t_cmd	*shell_parser_new_redirection_cmd(t_cmd *subcmd, char *file, int mode, int fd)
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


t_cmd	*shell_parser_redirection(t_cmd *cmd, char **p_input, char *end)
{
	int tok;
  char *q, *eq;

  while(shell_parser_helper_strings_whitespaces(p_input, end, "12<>"))
  {
		if ((**p_input == '1' || **p_input == '2') && (*p_input)[1] != '>')
			break;
		tok = tokenizer(p_input, end, 0, 0);
		tokenizer(p_input, end, &q, &eq);
		if (tok == '<')
			cmd = shell_parser_new_redirection_cmd(cmd, q, O_RDONLY, 0);
		if (tok == '>')
			cmd = shell_parser_new_redirection_cmd(cmd, q, O_RDWR | O_CREAT, 1);
		if (tok == '+')
			cmd = shell_parser_new_redirection_cmd(cmd, q, O_RDWR | O_CREAT | O_APPEND, 1);
		if (tok == '*')
			cmd = shell_parser_new_redirection_cmd(cmd, q, O_RDWR | O_CREAT, 2);
		if (tok == '>')
			cmd = shell_parser_new_redirection_cmd(cmd, q, O_RDWR | O_CREAT | O_APPEND, 2);
  }
  return (cmd);
}


t_cmd		*shell_parser_exec(char **p_input, char *end)
{
	char		*new_cmd;
	char		*new_cmd_end;
	int			tok;
	int			argc;
	t_exec_cmd	*cmd;
	t_cmd		*ret;

	ret = shell_parser_new_exec_cmd();
	cmd = (t_exec_cmd *)ret;
	argc = 0;
	ret = shell_parser_redirection(ret, p_input, end);
	while (*p_input < end)
	{
		if((tok = tokenizer(p_input, end, &new_cmd, &new_cmd_end)) == 0)
			break;
		if(tok != 'a')
			ft_putendl_fd("Syntax error", 1);
		if (argc >= MAXARGS)
		{
			ft_putendl_fd("Too long", 1);
			exit(0);
		}
		printf("tok = %c\n", tok);
		cmd->argv[argc] = ft_strndup(new_cmd, new_cmd_end - new_cmd);
		ret = shell_parser_redirection(ret, p_input, end);
		argc++;
	}
	cmd->argv[argc] = 0;
	return (ret);
}

t_cmd		*shell_parser_pipe(char **p_input, char *end)
{
	t_cmd	*cmd;
	char	*new_cmd;
	char	*new_cmd_end;

	if (shell_parser_helper_strings_scan(p_input, end, "|", &new_cmd, &new_cmd_end))
	{
		cmd = shell_parser_exec(&new_cmd, new_cmd_end);
		(*p_input)++;
		cmd = shell_parser_new_pipe_cmd(cmd, shell_parser_pipe(p_input, end));
	}
	else
		cmd = shell_parser_exec(&new_cmd, new_cmd_end);
	return (cmd);
}

t_cmd		*shell_parser(char *input)
{
	char	*end;
	t_cmd	*cmd;

	end = input + ft_strlen(input);
	cmd = shell_parser_pipe(&input, end);
	if(input != end)
		ft_putendl_fd("Syntax error", 1);
	return (cmd);
}
