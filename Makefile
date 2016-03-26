#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bjamin	  <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/15 14:57:05 by bjamin            #+#    #+#              #
#    Updated: 2016/01/06 13:31:31 by bjamin           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

#Define the program
NAME			= 21sh
LIB				=	./libft/libft.a
_SRC			= 	shell.c \
					shell_cmd.c \
					shell_env.c \
					shell_errors.c \
					shell_signals.c \
					builtins/shell_builtins.c \
					builtins/shell_builtins_pwd.c \
					builtins/shell_builtins_exit.c \
					builtins/shell_builtins_help.c \
					builtins/shell_builtins_cd.c \
					builtins/shell_builtins_env.c \
					builtins/shell_builtins_setenv.c \
					builtins/shell_builtins_unsetenv.c \
					builtins/helpers/shell_builtins_options_parser.c \
					builtins/helpers/shell_builtins_helpers_cd.c

INCLUDES		= -I./libft/includes/ -I./includes/
SRC				= $(addprefix srcs/,$(_SRC))
OBJ				= $(SRC:.c=.o)
CFLAGS			= -Wall -Wextra -Werror -g -ggdb

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft/
	@gcc $(CFLAGS) $(OBJ) $(LIB) $(INCLUDES) -o $(NAME)
	@echo $(NAME)" compiled"


%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

.PHONY: clean fclean re

clean:
	@rm -f $(OBJ)
	@make clean -C libft
	@echo "Clean all .o files"

fclean:	clean
	@make fclean -C libft
	@/bin/rm -rf $(NAME)
	@echo "Clean all .o and .a"

re: fclean all
