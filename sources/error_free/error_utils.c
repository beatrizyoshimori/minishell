/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:04:10 by byoshimo          #+#    #+#             */
/*   Updated: 2023/06/03 19:14:52 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *str1, char *str2, char *str3, int exit_status)
{
	int	backup_fd;

	if (g_ms.on_fork)
	{
		backup_fd = dup(1);
		dup2(2, 1);
		printf("%s%s: %s\n", str1, str2, str3);
		dup2(backup_fd, 1);
		close(backup_fd);
	}
	else
	{
		ft_putstr_fd(str1, 2);
		ft_putstr_fd(str2, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str3, 2);
		ft_putstr_fd("\n", 2);
	}
	g_ms.exit_status = exit_status;
}
