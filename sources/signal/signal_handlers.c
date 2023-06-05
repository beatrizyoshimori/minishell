/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 19:40:21 by byoshimo          #+#    #+#             */
/*   Updated: 2023/06/05 17:04:42 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signal)
{
	if (signal == SIGINT && !g_ms.on_fork)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else if (signal == SIGINT && g_ms.on_fork == 1)
		ft_putchar_fd('\n', 1);
	if (signal == SIGPIPE)
	{
		print_error("", "bilu", "Broken pipe", 141);
		exit_process(g_ms.token_list);
	}
}

void	signal_handler_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		g_ms.exit_status = 148;
		close(g_ms.fd_heredoc);
		exit_process(g_ms.token_list);
	}
}
