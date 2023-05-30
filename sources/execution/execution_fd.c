/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_fd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:55:52 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/29 21:58:29 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(t_token *token_list)
{
	int		i;
	t_token	*aux;

	aux = token_list;
	while (aux)
	{
		if (aux->redirect % REDIRECT_INPUT == 0)
			close(aux->fd[0]);
		if (aux->redirect % REDIRECT_OUTPUT == 0)
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

void	create_pipes(void)
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

void	set_fd(t_token *token, int i)
{
	if (token->redirect % REDIRECT_INPUT == 0)
		dup2(token->fd[0], 0);
	else if (i > 0)
		dup2(g_ms.pipe_fd[2 * (i - 1)], 0);
	if (token->redirect % REDIRECT_OUTPUT == 0)
		dup2(token->fd[1], 1);
	else if (i < (g_ms.num_tokens + 1) / 2 - 1)
		dup2(g_ms.pipe_fd[2 * i + 1], 1);
}
