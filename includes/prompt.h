/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:24:29 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/20 14:15:23 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <libft.h>
# include <termios.h>
# include <term.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>

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
# define IGNORE_1 ((buf[0] == 27 && buf[1] == 91 && buf[2] == 49))
# define QUIT ((buf[0] == 4 && buf[1] == 0 && buf[2] == 0))

# define COPY_MODE ((buf[0] == -50 && buf[1] == -87 && buf[2] == 0))
# define COPY ((buf[0] == -61 && buf[1] == -89 && buf[2] == 0))
# define PASTE ((buf[0] == -30 && buf[1] == -120 && buf[2] == -102))
# define CUT ((buf[0] == -30 && buf[1] == -119 && buf[2] == -120))

enum			e_prompt_status
{
	TRYING,
	READING,
	FIRE_CMD
};

typedef struct winsize	t_winsize;
typedef struct dirent	t_dirent;
typedef struct termios	t_termios;

typedef struct			s_prompt
{
	t_list				*chars;
	int					cursor_index;
	int					lenght;
	int					copy_mode;
	int					copy_start;
	int					copy_end;
	char				*copy_word;

}						t_prompt;

void					free_char(void *content, size_t size);
int						tputs_putchar(int c);
void					shell_prompt_display(int show_cursor);
int						shell_prompt_init(void);
int						shell_prompt_reset(void);
int						shell_prompt_update_window(void);
void					shell_prompt_add_new(void);
char					*shell_prompt_input(void);
char					*shell_prompt_get_command(
	t_prompt *prompt, size_t start, size_t end);
enum e_prompt_status	prompt_move_next_word(char *buf);
enum e_prompt_status	prompt_move_last_word(char *buf);
enum e_prompt_status	prompt_move_to_last_prompt(char *buf);
enum e_prompt_status	prompt_move_to_next_prompt(char *buf);
enum e_prompt_status	prompt_delete_char(char *buf);
enum e_prompt_status	prompt_delete_next_char(char *buf);
void					prompt_insert_one_char(char car);
enum e_prompt_status	prompt_insert_char(char *buf);
enum e_prompt_status	prompt_move_start(char *buf);
enum e_prompt_status	prompt_move_end(char *buf);
enum e_prompt_status	prompt_move_up(char *buf);
enum e_prompt_status	prompt_move_down(char *buf);
enum e_prompt_status	prompt_move_left(char *buf);
enum e_prompt_status	prompt_move_right(char *buf);
enum e_prompt_status	prompt_ignore_input(char *buf);
enum e_prompt_status	prompt_autocompletion(char *buf);
enum e_prompt_status	prompt_fire_cmd(char *buf);
enum e_prompt_status	prompt_shell_quit(char *buf);
enum e_prompt_status	prompt_copy_mode(char *buf);
enum e_prompt_status	prompt_copy(char *buf);
enum e_prompt_status	prompt_cut(char *buf);
enum e_prompt_status	prompt_paste(char *buf);

#endif
