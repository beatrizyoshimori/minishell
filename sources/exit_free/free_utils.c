/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:12:32 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/26 19:48:45 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ptrptr(char **tokens)
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
		free_ptrptr((*token_list)->token);
		free((*token_list)->pathname);
		free(*token_list);
		(*token_list) = aux;
	}
	unlink(".h*e*r*e*d*o*c*");
}
