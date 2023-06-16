/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 19:48:34 by byoshimo          #+#    #+#             */
/*   Updated: 2023/06/16 19:24:12 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_processes(t_token *token_list, int num_proc)
{
	int		i;
	int		status;
	t_token	*aux;

	aux = token_list;
	i = 0;
	while (i < num_proc)
	{
		waitpid(g_ms.pid[i], &status, 0);
		if (WIFEXITED(status))
			g_ms.exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_ms.exit_status = 128 + WTERMSIG(status);
		i++;
		if (i != num_proc)
			aux = aux->next->next;
	}
	signal_handler_parent();
}

static void	start_child_process(t_token *token_list, t_token *token, int i)
{
	set_fd(token, i);
	close_fd(token_list);
	if (!token->no_exec)
		exec_command_child(token_list, token);
	exit_process(token_list);
}

static void	start_processes_aux(t_token *token_list, t_token *token, int i)
{
	if (!ft_isdirectory(token->token[0]))
	{
		set_pathname(token);
		if (!token->pathname && !token->no_exec && !ft_isbuiltin(token))
		{
			print_error("", token->token[0], "command not found", 127);
			token->no_exec = 1;
		}
	}
	else
	{
		print_error("bilu: ", token->token[0], "Is a directory", 126);
		token->no_exec = 1;
	}
	g_ms.on_fork = 1;
	signal_handler_child();
	g_ms.pid[i] = fork();
	if (!g_ms.pid[i])
		start_child_process(token_list, token, i);
	g_ms.on_fork = 0;
}

void	start_processes(t_token *token_list)
{
	int		i;
	int		num_proc;
	t_token	*aux;

	create_pipes();
	num_proc = (g_ms.num_tokens + 1) / 2;
	g_ms.pid = (pid_t *)ft_calloc(num_proc + 1, sizeof(pid_t));
	aux = token_list;
	i = 0;
	while (i < num_proc)
	{
		start_processes_aux(token_list, aux, i);
		i++;
		if (i != num_proc)
			aux = aux->next->next;
	}
	close_fd(token_list);
	wait_processes(token_list, num_proc);
	free(g_ms.pipe_fd);
	g_ms.pipe_fd = NULL;
	free(g_ms.pid);
	g_ms.pid = NULL;
}
