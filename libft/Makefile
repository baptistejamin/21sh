# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/24 12:39:51 by bjamin            #+#    #+#              #
#    Updated: 2016/03/14 19:01:30 by bjamin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#Define the libft
LIB				= libft.a
_SRC			= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
					ft_isprint.c ft_toupper.c ft_tolower.c ft_strlen.c \
					ft_strcmp.c ft_strncmp.c ft_strcpy.c ft_strncpy.c \
					ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c \
					ft_strrchr.c ft_bzero.c ft_memset.c ft_memcpy.c \
					ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
					ft_strdup.c ft_strstr.c ft_strnstr.c ft_atoi.c \
					ft_memalloc.c ft_memdel.c  ft_strnew.c  ft_strdel.c \
					ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c \
					ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c \
					ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c \
					ft_putchar.c  ft_putstr.c ft_putendl.c ft_putnbr.c \
					ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
					ft_putnbr_fd.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c \
					ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_nblen.c \
					ft_swap.c ft_show_tab.c ft_sqrt.c ft_strcut.c \
					ft_str_to_tab.c ft_strfjoin.c get_next_line.c \
					ft_lstiter_if.c ft_lstsort.c ft_lstrev.c ft_free_tab.c \
					ft_is_in.c ft_lstdel_at.c ft_lstcount.c ft_lstcpy.c

SRC				= $(addprefix srcs/,$(_SRC))
INCLUDES		= ./includes/
OBJ     		= $(SRC:.c=.o)
CFLAGS			= -Wall -Wextra -Werror -g

all: $(LIB)

$(LIB):	$(OBJ)
	@ar rc $(LIB) $(OBJ)
	@ranlib $(LIB)
	@echo "libft.a compiled"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES)

.PHONY: clean fclean re

clean:
	@rm -rf $(OBJ)
	@echo "Clean all .o files"

fclean: clean
	@rm -rf $(LIB)
	@echo "Clean all .o and .a"

re: fclean all
