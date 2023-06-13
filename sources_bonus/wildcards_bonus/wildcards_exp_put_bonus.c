/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_exp_put_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:07:02 by lucade-s          #+#    #+#             */
/*   Updated: 2023/06/13 17:21:20 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	put_wildcards(t_token *token, int *i, char *first_path, t_list *wildcards)
{
	int		aux_i;
	int		j;
	int		l;
	char	**cp_token;
	t_list	*aux_wildcards;

	j = 0;
	while (token->token[j])
		j++;
	j--;
	aux_wildcards = wildcards;
	l = 0;
	while (aux_wildcards)
	{
		if (((char *)aux_wildcards->content)[0])
			l++;
		aux_wildcards = aux_wildcards->next;
	}
	j += l;
	aux_i = *i;
	*i += l - 1;
	cp_token = copy_ptrptr(token->token);
	free_ptrptr(token->token);
	token->token = (char **)ft_calloc(j + 1, sizeof(char *));
	j = 0;
	while (j < aux_i)
	{
		token->token[j] = ft_strdup(cp_token[j]);
		j++;
	}
	aux_i++;
	aux_wildcards = wildcards;
	while (aux_wildcards)
	{
		if (((char *)aux_wildcards->content)[0])
		{
			if (!first_path)
				token->token[j] = ft_strdup((char *)aux_wildcards->content);
			else
				token->token[j] = ft_strjoin(first_path, (char *)aux_wildcards->content);
			j++;
		}
		aux_wildcards = aux_wildcards->next;
	}
	while (cp_token[aux_i])
	{
		token->token[j] = ft_strdup(cp_token[aux_i]);
		aux_i++;
		j++;
	}
	free_ptrptr(cp_token);
}
