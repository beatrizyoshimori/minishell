/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:39:12 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/13 18:14:33 by byoshimo         ###   ########.fr       */
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

void	set_tokens(char **tokens, t_token **token_list, t_ms *ms)
{
	t_token	*new;

	ms->num_tokens = 0;
	while (tokens[ms->num_tokens])
	{
		new = (t_token *)malloc(sizeof(t_token));
		new->token = ft_split(tokens[ms->num_tokens], -6);
		new->ms = ms;
		new->next = NULL;
		ft_tokenadd_back(token_list, new);
		ms->num_tokens++;
	}
}
