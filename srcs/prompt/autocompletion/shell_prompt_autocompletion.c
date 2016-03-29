/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_prompt_autocompletion.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void	show_result(t_list *elem)
{
	char *str = elem->content;
	ft_putendl(str);
}

void	shell_prompt_autocompletion_add_results_from_path(t_list **list, 
													char *path, char *search)
{
	int			search_len;
	int			results;
	t_dirent	*dirent;
	DIR 		*dir;

	results = 0;
	dir = opendir(path);
	search_len = ft_strlen(search);
	while (dir != NULL && ((dirent = readdir(dir)) != NULL) && (results < 2))
	{
		if (dirent->d_name[0] != '.' && ft_strncmp(dirent->d_name, search, search_len) == 0)
		{
			ft_lstadd(list, ft_lstnew(dirent->d_name, ft_strlen(dirent->d_name) + 1));
			results++;
		}
	}
	if (dir)
		closedir(dir);
}

void	shell_prompt_autocompletion_search_as_path(t_list **list, char *search)
{
	char	*query;
	char	*query_path;

	query = ft_strrchr(search, '/') + 1;
	if (!*query)
		query = ft_strdup("");
	query_path = ft_strnew(ft_strlen(search) - ft_strlen(query) + 1);
	ft_strncpy(query_path, search, ft_strlen(search) - ft_strlen(query));
	shell_prompt_autocompletion_add_results_from_path(list, query_path, query);
}

char	*shell_prompt_autocompletion(char *search)
{
	t_sh	*sh;
	int		i;
	char	**path;
	char	*tmp;
	t_list	*results;
	char	*query;
	char	*query_path;

	results = NULL;
	sh = shell_recover();
	i = 0;
	if (ft_strrchr(search, '/'))
		shell_prompt_autocompletion_search_as_path(&results, search);
	else
	{
		query_path = ft_strdup("./");
		query = search;
		shell_prompt_autocompletion_add_results_from_path(&results, query_path, query);
		path = ft_strsplit(shell_env_get(sh->env_list, "PATH"), ':');
		while (path[i])
		{
			tmp = ft_strfjoin(ft_strjoin(path[i], "/"), query_path);
			shell_prompt_autocompletion_add_results_from_path(&results, tmp, query);
			i++;
			free(tmp);
		}
		if (path)
			ft_free_tab(path);
	}
	if (ft_lstcount(results) == 1)
		return (((char *)(results->content)) + ft_strlen(query));
	return (NULL);
}
