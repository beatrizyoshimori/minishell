/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:39:12 by byoshimo          #+#    #+#             */
/*   Updated: 2023/04/28 19:16:43 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_token_last(t_token *token)
{
	if (token == NULL)
		return (token);
	while (token->next != NULL)
		token = token->next;
	return (token);
}

void	ft_tokenadd_back(t_token **token, t_token *new)
{
	if (*token == NULL)
	{
		*token = new;
		return ;
	}
	ft_token_last(*token)->next = new;
}
