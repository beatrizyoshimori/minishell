/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 19:48:34 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/29 22:04:26 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_processes(t_token *token_list, int num_proc)
{
	int		i;
	int		status;
	t_token	*aux;

	aux = token_list;
	i = 0;
	while (i < num_proc)
	{
		waitpid(aux->pid, &status, 0);
		if (WIFEXITED(status))
			g_ms.exit_status = WEXITSTATUS(status);
		i++;
		if (i != num_proc)
			aux = aux->next->next;
	}
}

void	start_child_process(t_token *token_list, t_token *token, int i)
{
	set_fd(token, i);
	close_fd(token_list);
	if (!ft_isdirectory(token->token[0]))
	{
		set_pathname(token);
		if (!token->no_exec)
			exec_command_child(token_list, token);
	}
	else
	{
		print_error("bilu: ", token->token[0], "Is a directory");
		g_ms.exit_status = 126;
	}
	exit_execve(token_list);
}

void	start_processes(t_token *token_list)
{
	int		i;
	int		num_proc;
	t_token	*aux;

	create_pipes();
	num_proc = (g_ms.num_tokens + 1) / 2;
	aux = token_list;
	i = 0;
	while (i < num_proc)
	{
		g_ms.on_fork = 1;
		aux->pid = fork();
		if (!aux->pid)
			start_child_process(token_list, aux, i);
		i++;
		if (i != num_proc)
			aux = aux->next->next;
	}
	close_fd(token_list);
	wait_processes(token_list, num_proc);
	g_ms.on_fork = 0;
}
