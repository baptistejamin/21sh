/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 14:18:30 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/19 13:55:47 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "string.h"

# define BUFF_SIZE 32

typedef struct		s_gnl
{
	int				ret;
	char			*str;
	char			buf[BUFF_SIZE + 1];
}					t_gnl;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
size_t				ft_strlen(const char *str);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strcpy(char *dst, const char *str);
char				*ft_strncpy(char *dst, const char *str, size_t n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *restrict dst, const void *restrict src,
								int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strdup(const char *s1);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strfjoin(char *s1, char *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				**ft_str_to_tab(char const *s);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void				ft_lstiter_if(t_list *lst, void (*f)(t_list *e),
							int (*g)(t_list *e));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstsort(t_list **list, int (*cmp)(void *a_, void *b_),
						void *(*get_data)(t_list *e));
void				ft_lstdel_at(t_list **list, int at,
						void (*del)(void *, size_t));
int					ft_lstcount(t_list *list);
void				ft_lstcpy(t_list **dest, t_list *src);
void				ft_lstrev(t_list **list);
int					ft_nblen(int nb);
void				ft_swap(int *a, int *b);
int					ft_get_min(int a, int b);
int					ft_get_min_three(int a, int b, int c);
void				ft_show_tab(int *tab, int size);
int					ft_sqrt(int nb);
int					ft_strcut(char **s1, char **s2, char c);
void				ft_free_tab(char **tab);
int					get_next_line(int const fd, char **line);
int					ft_is_in(char *str, char c);

#endif
