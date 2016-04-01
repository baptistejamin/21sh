/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:24:29 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/20 14:15:23 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include <libft.h>

//todo, generic allocation
#define MAXARGS 10

enum	e_cmd_type
{
	EXEC,
	REDIRECTION,
	PIPE,
	ERRROR
};

typedef enum e_cmd_type	t_cmd_type;

typedef	struct 	s_cmd
{
	t_cmd_type 		type;
}								t_cmd;

typedef struct 	s_exec_cmd
{
	t_cmd_type 		type;
	char 					*argv[MAXARGS];
}								t_exec_cmd;

typedef	struct	s_redirection_cmd
{
	t_cmd_type		type;
	t_cmd					*cmd;
	char					*file;
	int						mode;
	int						fd;
}								t_redirection_cmd;

typedef	struct	s_pipe_cmd
{
	t_cmd_type		type;
	t_cmd					*left;
	t_cmd					*right;
};

t_cmd  	*shell_parser(char *input);
t_cmd		*shell_parser_new_exec_cmd(void);
t_cmd		*shell_parser_new_redirection_cmd(t_cmd *subcmd, char *file, int mode, int fd);
t_cmd		*shell_parser_new_pipe_cmd(t_cmd *left, t_cmd *right);

#endif
