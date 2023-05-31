/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:04:10 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/30 20:45:54 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *str1, char *str2, char *str3, int exit_status)
{
	int	num_proc;
	int	process;

	if (g_ms.on_fork)
	{
		process = 0;
		while (g_ms.pid[process])
			process++;
		num_proc = (g_ms.num_tokens + 1) / 2;
		if (process == num_proc - 1)
			g_ms.print_error = 1;
		while (!g_ms.print_error)
			;
	}
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str3, 2);
	ft_putstr_fd("\n", 2);
	g_ms.exit_status = exit_status;
	if (g_ms.on_fork && process >= 1)
		kill(g_ms.pid[process - 1], SIGUSR1);
}
