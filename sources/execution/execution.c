/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 19:48:34 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/24 22:09:48 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(t_token *token_list)
{
	t_token	*aux;

	aux = token_list;
	while (aux)
	{
		if (aux->redirect % REDIRECT_INPUT == 0)
			close(aux->fd[0]);
		if (aux->redirect % REDIRECT_OUTPUT == 0)
			close(aux->fd[1]);
		if (aux->token[0][0] == '|')
		{
			close(aux->fd[0]);
			close(aux->fd[1]);
		}
		aux = aux->next;
	}
}

static void	create_pipes(t_token *token_list)
{
	t_token *aux;

	aux = token_list->next;
	while (aux)
	{
		pipe(aux->fd);
		aux = aux->next->next;
	}
}

static void	set_fd(t_token *token, int i)
{
	if (token->redirect % REDIRECT_INPUT == 0)
		dup2(token->fd[0], 0);
	else if (i > 0)
		dup2(g_ms.prev_fd, 0);
	if (token->redirect % REDIRECT_OUTPUT == 0)
		dup2(token->fd[1], 1);
	else if (i < (g_ms.num_tokens + 1) / 2 - 1)
		dup2(token->next->fd[1], 1);
}

static void	exec_command(t_token *token_list, t_token *token)
{
	if (!ft_strncmp(token->token[0], "cd", 2))
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
	exit_command(token_list);
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
	pid_t	*pid;
	t_token	*aux;
	
	create_pipes(token_list);
	num_proc = (g_ms.num_tokens + 1) / 2;
	pid = (pid_t *)ft_calloc(num_proc + 1, sizeof(pid_t));
	aux = token_list;
	i = 0;
	while (i < num_proc)
	{
		if (aux->next)
			g_ms.prev_fd = aux->next->fd[0];
		pid[i] = fork();
		if (!pid[i])
		{
			set_fd(aux, i);
			//printf("prev fd: %i\n", g_ms.prev_fd);
			close_fd(token_list);
			close(g_ms.prev_fd);
			if (access(aux->token[0], F_OK) == 0)
			{
				// check_execution_permission(aux->token[0]);
				aux->pathname = ft_strdup(aux->token[0]);
			}
			else
				set_pathname(aux);
			free(pid);
			if (aux->token[0])
				exec_command(token_list, aux);
		}
		i++;
		if (i != num_proc)
			aux = aux->next->next;
	}
	close_fd(token_list);
	i = 0;
	while (i < num_proc)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	free(pid);
}
