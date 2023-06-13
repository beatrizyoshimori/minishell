/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:38:06 by lucade-s          #+#    #+#             */
/*   Updated: 2023/06/13 17:35:48 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	expand_wildcards(t_token *token, int i)
{
	int		j;
	char	*first_path;
	t_list	*wildcards;

	if (ft_strchr_wc(token->token[i])
		&& (i == 0 || (i > 0 && ft_strncmp(token->token[i - 1], "<<", 3))))
	{
		g_ms.first_wildcard = 1;
		j = get_first_path(token->token[i], &first_path);
		wildcards = get_wildcards_expansion(token->token[i] + j, first_path);
		if (j == 0)
		{
			free(first_path);
			first_path = NULL;
		}
		if (wildcards)
		{
			put_wildcards(token, &i, first_path, wildcards);
			free_list(&wildcards);
		}
		else
			change_back_asterisc(&token->token[i]);
		free(first_path);
	}
}

void	wildcards(t_token *token_list)
{
	int		i;
	t_token	*aux;

	aux = token_list;
	while (aux)
	{
		i = 0;
		while (aux->token[i])
		{
			expand_wildcards(aux, i);
			i++;
		}
		aux = aux->next;
	}
}
