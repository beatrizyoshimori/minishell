/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:59:18 by lucade-s          #+#    #+#             */
/*   Updated: 2023/06/16 19:19:21 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_process(t_token *token_list)
{
	close(0);
	close(1);
	close(2);
	close(g_ms.fd_heredoc);
	rl_clear_history();
	free_token_list(&token_list);
	free(g_ms.pipe_fd);
	free(g_ms.pid);
	free_ptrptr(g_ms.env);
	free(g_ms.home);
	exit(g_ms.exit_status);
}

void	exec_command_child(t_token *token_list, t_token *token)
{
	if (ft_isbuiltin(token))
		exec_builtin(token_list, token);
	else if (token->pathname)
	{
		if (execve(token->pathname, token->token, g_ms.env) == -1)
			print_error("", token->token[0], strerror(errno), errno);
	}
}
