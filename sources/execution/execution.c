/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 19:48:34 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/26 17:10:08 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fd(t_token *token_list)
{
	int		i;
	t_token	*aux;

	aux = token_list;
	while (aux)
	{
		if (aux->redirect % 2 == 0)
			close(aux->fd[0]);
		if (aux->redirect % 3 == 0)
			close(aux->fd[1]);
		aux = aux->next;
	}
	i = 0;
	while (i < g_ms.num_tokens - 1)
	{
		close(g_ms.pipe_fd[i]);
		i++;
	}
}

static void	create_pipes(void)
{
	int	i;

	g_ms.pipe_fd = (int *)ft_calloc(g_ms.num_tokens, sizeof(int));
	i = 0;
	while (i < g_ms.num_tokens - 1)
	{
		pipe(&g_ms.pipe_fd[i]);
		i += 2;
	}
}

static void	set_fd(t_token *token, int i)
{
	if (token->redirect % 2 == 0)
		dup2(token->fd[0], 0);
	else if (i > 0)
		dup2(g_ms.pipe_fd[2 * (i - 1)], 0);
	if (token->redirect % 3 == 0)
		dup2(token->fd[1], 1);
	else if (i < (g_ms.num_tokens + 1) / 2 - 1)
		dup2(g_ms.pipe_fd[2 * i + 1], 1);
}

static void	exit_builtin(t_token *token_list)
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

static void	exec_command_child(t_token *token_list, t_token *token)
{
	if (!ft_strncmp(token->token[0], "cd", 3))
		cd(token->token);
	else if (!ft_strncmp(token->token[0], "export", 7))
		export(token->token);
	else if (!ft_strncmp(token->token[0], "echo", 5))
		echo(token->token);
	else if (!ft_strncmp(token->token[0], "env", 4))
		env(token->token);
	else if (!ft_strncmp(token->token[0], "exit", 5))
		exit_command(token_list);
	else if (!ft_strncmp(token->token[0], "pwd", 4))
		pwd();
	else if (!ft_strncmp(token->token[0], "unset", 6))
		unset(token->token);
	else
		execve(token->pathname, token->token, g_ms.env);
	exit_builtin(token_list);
}

// void	check_execution_permission(char *pathname, t_data *data)
// {
// 	if (access(pathname, X_OK) == -1)
// 	{
// 		close(data->fd[0]);
// 		close(data->fd[1]);
// 		perror(pathname);
// 		free_all(data);
// 		exit(126);
// 	}
// }

static void	set_pathname(t_token *token)
{
	int		i;
	char	*tmp;

	i = 0;
	while (g_ms.paths[i])
	{
		tmp = ft_strjoin(g_ms.paths[i], "/");
		token->pathname = ft_strjoin(tmp, token->token[0]);
		if (tmp)
			free(tmp);
		if (access(token->pathname, F_OK) == 0)
		{
			// check_execution_permission(token->pathname, data);
			return ;
		}
		if (token->pathname)
			free(token->pathname);
		i++;
	}
	token->pathname = NULL;
}

void	start_processes(t_token *token_list)
{
	int		i;
	int		num_proc;
	int		status;
	pid_t	*pid;
	t_token	*aux;
	
	create_pipes();
	num_proc = (g_ms.num_tokens + 1) / 2;
	pid = (pid_t *)ft_calloc(num_proc + 1, sizeof(pid_t));
	aux = token_list;
	i = 0;
	while (i < num_proc)
	{
		pid[i] = fork();
		if (!pid[i])
		{
			set_fd(aux, i);
			close_fd(token_list);
			if (access(aux->token[0], F_OK) == 0)
			{
				// check_execution_permission(aux->token[0]);
				aux->pathname = ft_strdup(aux->token[0]);
			}
			else
				set_pathname(aux);
			free(pid);
			if (aux->token[0])
				exec_command_child(token_list, aux);
		}
		i++;
		if (i != num_proc)
			aux = aux->next->next;
	}
	close_fd(token_list);
	i = 0;
	while (i < num_proc)
	{
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
			g_ms.exit_status = WEXITSTATUS(status);
		i++;
	}
	free(pid);
}
