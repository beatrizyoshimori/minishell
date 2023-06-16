/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 19:40:21 by byoshimo          #+#    #+#             */
/*   Updated: 2023/06/16 17:28:02 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_ms.exit_status = 130;
	}
}

static void	handler_child(int signal)
{
	if (signal == SIGINT)
	{
		if (g_ms.on_fork != 2)
			ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		g_ms.exit_status = 130;
	}
	if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		rl_replace_line("", 0);
		g_ms.exit_status = 131;
	}
	if (signal == SIGPIPE)
	{
		print_error("", "bilu", "Broken pipe", 141);
		exit_process(g_ms.token_list);
	}
}

void	signal_handler_parent(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_handler_child(void)
{
	signal(SIGINT, handler_child);
	if (g_ms.on_fork == 1)
	{
		signal(SIGQUIT, handler_child);
		signal(SIGPIPE, handler_child);
	}
	else
		signal(SIGQUIT, SIG_IGN);
}

void	signal_handler_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		g_ms.exit_status = 130;
		close(g_ms.fd_heredoc);
		exit_process(g_ms.token_list);
	}
}
