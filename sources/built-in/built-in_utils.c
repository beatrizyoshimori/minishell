/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:52:49 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/29 20:34:06 by lucade-s         ###   ########.fr       */
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

void	exec_builtin(t_token *token_list)
{
	if (token_list->redirect % REDIRECT_INPUT == 0)
	{
		dup2(token_list->fd[0], 0);
		close(token_list->fd[0]);
	}
	if (token_list->redirect % REDIRECT_OUTPUT == 0)
	{
		dup2(token_list->fd[1], 1);
		close(token_list->fd[1]);
	}
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
