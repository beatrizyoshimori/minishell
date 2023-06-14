/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_exp_put_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:07:02 by lucade-s          #+#    #+#             */
/*   Updated: 2023/06/13 21:54:32 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	insert_wc(t_token *token, int *j, t_list *wildcards)
{
	t_list	*aux_wc;

	aux_wc = wildcards;
	while (aux_wc)
	{
		if (((char *)aux_wc->content)[0])
		{
			token->token[*j] = ft_strdup((char *)aux_wc->content);
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

static void	put_first_path(t_list *wildcards, char *first_path)
{
	char	*aux;
	t_list	*aux_wc;

	aux_wc = wildcards;
	while (aux_wc)
	{
		if (((char *)aux_wc->content)[0])
		{
			aux = ft_strdup((char *)aux_wc->content);
			free((char *)aux_wc->content);
			aux_wc->content = ft_strjoin(first_path, aux);
			free(aux);
		}
		aux_wc = aux_wc->next;
	}
}

static void	finish_wc(char *token_i, t_list **wildcards, char *first_path)
{
	if (first_path)
		put_first_path(*wildcards, first_path);
	if (token_i[ft_strlen(token_i) - 1] == '/')
		put_slash_dir(wildcards);
}

void	put_wildcards(t_token *token, int *i,
	char *first_path, t_list *wildcards)
{
	int		aux_i;
	int		j;
	char	**cp_token;

	finish_wc(token->token[*i], &wildcards, first_path);
	cp_token = copy_ptrptr(token->token);
	aux_i = *i;
	*i += remalloc(token, wildcards) - 1;
	j = 0;
	while (j < aux_i)
	{
		token->token[j] = ft_strdup(cp_token[j]);
		j++;
	}
	aux_i++;
	insert_wc(token, &j, wildcards);
	while (cp_token[aux_i])
	{
		token->token[j] = ft_strdup(cp_token[aux_i]);
		aux_i++;
		j++;
	}
	free_list(&wildcards);
	free_ptrptr(cp_token);
}
