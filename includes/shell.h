/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:24:29 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/20 14:15:23 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <libft.h>
# include <unistd.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <fcntl.h>
# include <termios.h>
# include <term.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>

# define UNUSED(x) (void)(x)
# define PATH_MAX 4096

# define SHIFT_UP ((buf[0] == 59 && buf[1] == 50 && buf[2] == 65))
# define UP ((buf[0] == 27 && buf[1] == 91 && buf[2] == 65))
# define SHIFT_DOWN ((buf[0] == 59 && buf[1] == 50 && buf[2] == 66))
# define DOWN ((buf[0] == 27 && buf[1] == 91 && buf[2] == 66))
# define SHIFT_RIGHT ((buf[0] == 59 && buf[1] == 50 && buf[2] == 67))
# define RIGHT ((buf[0] == 27 && buf[1] == 91 && buf[2] == 67))
# define SHIFT_LEFT ((buf[0] == 59 && buf[1] == 50 && buf[2] == 68))
# define LEFT ((buf[0] == 27 && buf[1] == 91 && buf[2] == 68))
# define BACK_SPACE ((buf[0] == 127 && buf[1] == 0 && buf[2] == 0))
# define DELETE ((buf[0] == 27 && buf[1] == 91 && buf[2] == 51))
# define ENTER ((buf[0] == 10 && buf[1] == 0 && buf[2] == 0))
# define HOME ((buf[0] == 27 && buf[1] == 91 && buf[2] == 72))
# define END ((buf[0] == 27 && buf[1] == 91 && buf[2] == 70))
# define TAB ((buf[0] == 9 && buf[1] == 0 && buf[2] == 0))

enum			e_prompt_status
{
	TRYING,
	READING,
	FIRE_CMD
};

typedef int	(*t_func)(void *sh, t_list *environ, char **cmds);

typedef struct termios	t_termios;
typedef struct winsize	t_winsize;
typedef struct stat		t_stat;
typedef struct dirent	t_dirent;

typedef struct		s_prompt
{
	t_list			*chars;
	int				cursor_index;
	int				lenght;
}					t_prompt;

typedef struct		s_builtin
{
	char			*name;
	t_func			func;
}					t_builtin;

typedef struct		s_generic_options
{
	char			options[256];
	int				start;
	int				error;
	int				error_char;
	int				options_counter;
}					t_generic_options;

typedef struct		s_env
{
	char			*var;
	char			*value;
}					t_env;

typedef struct		s_sh
{
	char			*term_name;
	int				tty;
	t_termios		term;
	t_winsize		win;
	t_list			*env_list;
	int				last_res;
	t_list			*history;
	int				prompt_position;
	t_prompt		*current_prompt;
}					t_sh;

t_sh				*shell_recover(void);

/*
* Prompt
*/
int					tputs_putchar(int c);
int					shell_prompt_display(t_sh *sh, int show_cursor);
int					shell_prompt_init(t_sh *sh);
int					shell_prompt_update_window(t_sh *sh);
void				shell_prompt_add_new(t_sh *sh);
char				*shell_prompt_input(t_sh *sh);
char				*shell_prompt_autocompletion(char *search);
char 				*shell_prompt_get_command(t_prompt *prompt, size_t start, size_t end);

/*
* Cmds
*/
int					shell_launch_cmd(t_sh *sh, t_list *environ,
									char *cmd, char **args);
/*
* Env
*/
void				shell_env_to_list(t_list **list, char **environ);
void				shell_env_show(t_list *list);
char				**shell_env_from_list(t_list *list);
char				*shell_env_get(t_list *list, char *var);
char				**shell_copy_env(char **env);
int					shell_count_env(char **env);

/*
* Signals
*/
void				shell_signals(void);

/*
* Buitlins
*/
int					shell_boot(t_sh *sh, t_list *environ, char **cmds);
int					shell_builtins_exit(void *sh_, t_list *environ,
									char **cmds);
int					shell_builtins_help(void *sh_, t_list *environ,
									char **cmds);
int					shell_builtins_pwd(void *sh_, t_list *environ,
									char **cmds);
int					shell_builtins_cd(void *sh, t_list *environ,
									char **cmds);
int					shell_builtins_env(void *sh_, t_list *environ,
									char **cmds);
int					shell_builtins_setenv_set(t_list **list,
									char *var, char *value);
void				shell_builtins_setenv_add(t_list **list, char *var,
									char *value);
int					shell_builtins_setenv(void *sh_,
									t_list *environ, char **cmds);
int					shell_builtins_unsetenv(void *sh_, t_list *environ,
								char **cmds);
void				shell_builtins_unsetenv_free(void *content,
								size_t content_size);
int					shell_is_builtin(t_sh *sh, char **cmds);
int					shell_boot_builtin(t_sh *sh, t_list *environ,
								char **cmds);
int					shell_boot_cmd(t_sh *sh, t_list *environ,
								char **cmds);
void				shell_errors_is_directory(char *cmd);
void				shell_errors_not_found(char *cmd);
void				shell_errors_no_file_directory(char *cmd);
t_generic_options	shell_builtins_options_parser(char **cmds,
							char *managed_options);
int					shell_builtins_cd_change_directory(t_sh *sh,
							t_list **environ, char *curpath, int is_physical);
void				shell_builtins_cd_update_path(t_sh *sh,
							t_list **environ, char *old_path, char *path);
char				*shell_builtins_cd_assert_multiple_args(t_sh *sh,
							char **cmds, t_generic_options *options);
char				*shell_builtins_cd_assert_home(t_sh *sh,
							t_list *environ);
int					shell_builtins_cd_error(int type, char *path);

#endif
