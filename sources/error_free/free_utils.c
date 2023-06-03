/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:12:32 by byoshimo          #+#    #+#             */
/*   Updated: 2023/06/03 19:27:46 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ptrptr(char **ptrptr)
{
	int	i;

	i = 0;
	while (ptrptr[i])
	{
		free(ptrptr[i]);
		i++;
	}
	free(ptrptr);
	ptrptr = NULL;
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
	if (g_ms.on_fork != 2)
		unlink(".h*e*r*e*d*o*c*");
}
