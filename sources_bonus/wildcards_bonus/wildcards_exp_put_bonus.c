/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_exp_put_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:07:02 by lucade-s          #+#    #+#             */
/*   Updated: 2023/06/13 18:06:33 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	insert_wc(t_token *token, int *j, t_list *wc, char *first_path)
{
	t_list	*aux_wc;

	aux_wc = wc;
	while (aux_wc)
	{
		if (((char *)aux_wc->content)[0])
		{
			if (!first_path)
				token->token[*j] = ft_strdup((char *)aux_wc->content);
			else
				token->token[*j] = ft_strjoin(first_path,
						(char *)aux_wc->content);
			(*j)++;
		}
		aux_wc = aux_wc->next;
	}
}

static int	remalloc(t_token *token, t_list *wildcards)
{
	int		j;
	int		l;
	t_list	*aux_wildcards;

	j = 0;
	while (token->token[j])
		j++;
	j--;
	l = 0;
	aux_wildcards = wildcards;
	while (aux_wildcards)
	{
		if (((char *)aux_wildcards->content)[0])
			l++;
		aux_wildcards = aux_wildcards->next;
	}
	j += l;
	free_ptrptr(token->token);
	token->token = (char **)ft_calloc(j + 1, sizeof(char *));
	return (l);
}

void	put_wildcards(t_token *token, int *i, char *first_path, t_list *wc)
{
	int		aux_i;
	int		j;
	char	**cp_token;

	cp_token = copy_ptrptr(token->token);
	aux_i = *i;
	*i += remalloc(token, wc) - 1;
	j = 0;
	while (j < aux_i)
	{
		token->token[j] = ft_strdup(cp_token[j]);
		j++;
	}
	aux_i++;
	insert_wc(token, &j, wc, first_path);
	while (cp_token[aux_i])
	{
		token->token[j] = ft_strdup(cp_token[aux_i]);
		aux_i++;
		j++;
	}
	free_ptrptr(cp_token);
}
