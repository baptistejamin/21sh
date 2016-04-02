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
#include <fcntl.h>

//todo, generic allocation
#define MAXARGS 10
#define WHITESPACES " \t\r\n\v"
#define TOKENS "<|>"


#define	M_READ (O_RDONLY | O_NONBLOCK | O_CREAT)
#define M_READ_TRUNC (O_RDONLY | O_NONBLOCK | O_CREAT | O_TRUNC)
#define M_READ_APPEND (O_RDONLY | O_NONBLOCK | O_CREAT | O_APPEND)
#define M_WRITE_TRUNC (O_WRONLY | O_NONBLOCK | O_CREAT | O_TRUNC)
#define M_WRITE_APPEND (O_WRONLY | O_NONBLOCK | O_CREAT | O_APPEND)

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
	t_cmd_type 	type;
}				t_cmd;

typedef struct 	s_exec_cmd
{
	t_cmd_type 	type;
	t_list		*argv;
}				t_exec_cmd;

typedef	struct	s_redirection_cmd
{
	t_cmd_type		type;
	t_cmd			*cmd;
	char			*file;
	int				mode;
	int				fd;
}					t_redirection_cmd;

typedef	struct	s_pipe_cmd
{
	t_cmd_type		type;
	t_cmd			*left;
	t_cmd			*right;
}					t_pipe_cmd;

int 		tokenizer(char **p_input, char *end, char **new_cmd, char **new_cmd_end);
t_cmd		*shell_parser(char *input);
t_cmd		*shell_parser_new_exec_cmd(void);
t_cmd		*shell_parser_new_redirection_cmd(t_cmd *subcmd, char *file, int mode, int fd);
t_cmd		*shell_parser_new_pipe_cmd(t_cmd *left, t_cmd *right);
int			shell_parser_helper_strings_scan_pipes(char **p_input, char *end,
							char **new_cmd, char **new_cmd_end);
int			shell_parser_helper_strings_whitespaces(char **p_input, char *end,
							char *search);


#endif
