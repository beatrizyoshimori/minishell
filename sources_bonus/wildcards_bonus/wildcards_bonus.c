/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:38:06 by lucade-s          #+#    #+#             */
/*   Updated: 2023/06/13 17:13:51 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	wildcards(t_token *token_list)
{
	int		i;
	int		j;
	char	*first_path;
	t_token	*aux;
	t_list	*wildcards;

	aux = token_list;
	while (aux)
	{
		i = 0;
		while (aux->token[i])
		{
			if (ft_strchr_wc(aux->token[i]) && (i == 0 || (i > 0 && ft_strncmp(aux->token[i - 1], "<<", 3))))
			{
				g_ms.first_wildcard = 1;
				j = get_first_path(aux->token[i], &first_path);
				wildcards = expand_wildcards(aux->token[i] + j, first_path);
				if (j == 0)
				{
					free(first_path);
					first_path = NULL;
				}
				if (wildcards)
				{
					put_wildcards(aux, &i, first_path, wildcards);
					free_list(&wildcards);
				}
				else
					change_back_asterisc(&aux->token[i]);
				free(first_path);
			}
			i++;
		}
		aux = aux->next;
	}
}
