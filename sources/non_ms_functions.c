/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_ms_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:56:42 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/31 17:27:55 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_token *token_list)
{
	int		i;
	t_token	*aux;

	aux = token_list;
	while (aux)
	{
		i = 0;
		while (aux->token[i])
		{
			printf("%s\n", aux->token[i]);
			i++;
		}
		printf("\n");
		aux = aux->next;
	}
}
