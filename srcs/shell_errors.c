/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void	shell_errors_is_directory(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": is a directory\n", 2);
}

void	shell_errors_not_found(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	shell_errors_no_file_directory(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}
