/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:52:49 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/29 21:10:35 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_fd_back(int redirect)
{
	if (redirect % REDIRECT_INPUT == 0)
		dup2(g_ms.backup_fd[0], 0);
	if (redirect % REDIRECT_OUTPUT == 0)
		dup2(g_ms.backup_fd[1], 1);
}

static void	set_fd_builtin(int redirect, int fd[2])
{
	if (redirect % REDIRECT_INPUT == 0)
	{
		dup2(fd[0], 0);
		close(fd[0]);
	}
	if (redirect % REDIRECT_OUTPUT == 0)
	{
		dup2(fd[1], 1);
		close(fd[1]);
	}
}

void	exec_builtin(t_token *token_list)
{
	set_fd_builtin(token_list->redirect, token_list->fd);
	if (token_list->type == CD)
		cd(token_list->token);
	else if (token_list->type == ECHO)
		echo(token_list->token);
	else if (token_list->type == ENV)
		env(token_list->token);
	else if (token_list->type == EXIT)
		exit_command(token_list);
	else if (token_list->type == EXPORT)
		export(token_list->token);
	else if (token_list->type == PWD)
		pwd();
	else if (token_list->type == UNSET)
		unset(token_list->token);
	change_fd_back(token_list->redirect);
}

int	ft_isbuiltin(t_token *token_list)
{
	if (!ft_strncmp(token_list->token[0], "cd", 3))
		token_list->type = CD;
	else if (!ft_strncmp(token_list->token[0], "echo", 5))
		token_list->type = ECHO;
	else if (!ft_strncmp(token_list->token[0], "env", 4))
		token_list->type = ENV;
	else if (!ft_strncmp(token_list->token[0], "exit", 5))
		token_list->type = EXIT;
	else if (!ft_strncmp(token_list->token[0], "export", 7))
		token_list->type = EXPORT;
	else if (!ft_strncmp(token_list->token[0], "pwd", 4))
		token_list->type = PWD;
	else if (!ft_strncmp(token_list->token[0], "unset", 6))
		token_list->type = UNSET;
	if (token_list->type >= CD && token_list->type <= UNSET)
		return (1);
	return (0);
}
