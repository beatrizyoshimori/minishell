/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:39:12 by byoshimo          #+#    #+#             */
/*   Updated: 2023/06/15 22:17:03 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*ft_token_last(t_token *token)
{
	if (token == NULL)
		return (token);
	while (token->next != NULL)
		token = token->next;
	return (token);
}

static void	ft_tokenadd_back(t_token **token_list, t_token *new)
{
	if (*token_list == NULL)
	{
		*token_list = new;
		return ;
	}
	ft_token_last(*token_list)->next = new;
}

void	set_tokens(char **tokens, t_token **token_list)
{
	t_token	*new;

	g_ms.num_tokens = 0;
	while (tokens[g_ms.num_tokens])
	{
		new = (t_token *)malloc(sizeof(t_token));
		new->token = ft_split(tokens[g_ms.num_tokens], SPACE_OUT_QUOTES);
		new->redirect = NO_REDIRECT;
		new->no_exec = 0;
		new->type = 0;
		new->fd[0] = 0;
		new->fd[1] = 0;
		new->pathname = NULL;
		new->next = NULL;
		ft_tokenadd_back(token_list, new);
		g_ms.num_tokens++;
	}
}
