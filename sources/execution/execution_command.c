/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_cmd_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:59:18 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/29 22:00:05 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_execve(t_token *token_list)
{
	close(0);
	close(1);
	rl_clear_history();
	free_token_list(&token_list);
	free(g_ms.pipe_fd);
	free_ptrptr(g_ms.paths);
	free_ptrptr(g_ms.env);
	free(g_ms.home);
	exit(g_ms.exit_status);
}

static void	make_execve(t_token *token)
{
	if (execve(token->pathname, token->token, g_ms.env) == -1)
	{
		if (!g_ms.printed_error)
		{
			print_error("", token->token[0], strerror(errno));
			g_ms.exit_status = errno;
		}
	}
}

void	exec_command_child(t_token *token_list, t_token *token)
{
	if (!ft_strncmp(token->token[0], "cd", 3))
		cd(token->token);
	else if (!ft_strncmp(token->token[0], "echo", 5))
		echo(token->token);
	else if (!ft_strncmp(token->token[0], "env", 4))
		env(token->token);
	else if (!ft_strncmp(token->token[0], "exit", 5))
		exit_command(token_list);
	else if (!ft_strncmp(token->token[0], "export", 7))
		export(token->token);
	else if (!ft_strncmp(token->token[0], "pwd", 4))
		pwd();
	else if (!ft_strncmp(token->token[0], "unset", 6))
		unset(token->token);
	else if (token->pathname)
		make_execve(token);
	else if (!token->pathname)
	{
		print_error("", token->token[0], "command not found");
		g_ms.exit_status = 127;
	}
}
