/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 19:48:34 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/27 19:57:47 by lucade-s         ###   ########.fr       */
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

static void	exit_execve(t_token *token_list)
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
	else if (token->pathname)
	{
		if (execve(token->pathname, token->token, g_ms.env) == -1)
		{
			if (!g_ms.print_error)
			{
				ft_putstr_fd(token->token[0], 2);
				ft_putstr_fd(": ", 2);
				ft_putstr_fd(strerror(errno), 2);
				ft_putstr_fd("\n", 2);
				g_ms.exit_status = errno;
			}
		}
	}
	else if (!token->pathname)
	{
		ft_putstr_fd(token->token[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		g_ms.exit_status = 127;
	}
}

// void	check_execution_permission(t_token *token_list, t_token *token)
// {
// 	if (access(token->pathname, X_OK) == -1)
// 	{
// 		token->exec = 1;
// 		g_ms.exit_status = 126;
// 		exit_execve(token_list);
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
			// check_execution_permission(token_list, token);
			return ;
		}
		if (token->pathname)
			free(token->pathname);
		i++;
	}
	token->pathname = NULL;
}

static int	ft_isdirectory(char *token_cmd)
{
	struct stat	statbuf;

	if (stat(token_cmd, &statbuf) != 0)
		return (0);
	if (S_ISDIR(statbuf.st_mode))
	{
		if (*token_cmd == '.')
			token_cmd++;
		if (*token_cmd == '.')
			token_cmd++;
		if (*token_cmd == '/')
			return (1);
	}
	return (0);
}

static int	ft_isfile(char *token_cmd)
{
	if (*token_cmd == '.')
		token_cmd++;
	if (*token_cmd == '.')
		token_cmd++;
	if (*token_cmd == '/')
		return (1);
	return (0);
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
			if (!ft_isdirectory(aux->token[0]))
			{
				if (aux->token[0][0] == '/' && access(aux->token[0], F_OK) == 0)
				{
					// check_execution_permission(token_list, aux);
					aux->pathname = ft_strdup(aux->token[0]);
				}
				else if (ft_isfile(aux->token[0]) && access(aux->token[0], F_OK) == -1)
				{
					ft_putstr_fd("bilu: ", 2);
					ft_putstr_fd(aux->token[0], 2);
					ft_putstr_fd(": ", 2);
					ft_putstr_fd(strerror(errno), 2);
					ft_putstr_fd("\n", 2);
					aux->exec = 1;
					g_ms.exit_status = 127;
				}
				else
					set_pathname(aux);
				if (!aux->exec)
					exec_command_child(token_list, aux);
			}
			else
			{
				ft_putstr_fd("bilu: ", 2);
				ft_putstr_fd(aux->token[0], 2);
				ft_putstr_fd(": Is a directory\n", 2);
				g_ms.exit_status = 126;
			}
			free(pid);
			exit_execve(token_list);
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
