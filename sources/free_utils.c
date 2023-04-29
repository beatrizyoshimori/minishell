/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:12:32 by byoshimo          #+#    #+#             */
/*   Updated: 2023/04/29 18:29:48 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
	tokens = NULL;
}

void	free_token_list(t_token **token_list)
{
	t_token	*aux;

	while (*token_list)
	{
		aux = (*token_list)->next;
		free(*token_list);
		(*token_list) = aux;
	}
}
