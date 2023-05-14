/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 20:30:57 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/14 20:16:49 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_syntax_error(t_token **token_list, char c)
{
	ft_putstr_fd("bilu: syntax error near unexpected token ", 2);
	if (c == '\n')
		ft_putstr_fd("'newline'\n", 2);
	else
	{
		ft_putchar_fd('\'', 2);
		ft_putchar_fd(c, 2);
		ft_putstr_fd("'\n", 2);
	}
	exit_program(token_list);
}

void	remove_quotes_aux(char **token_i)
{
	int		i;
	char	*aux;
	char	**split;

	aux = (char *)ft_calloc(1, sizeof(char));
	split = ft_split(*token_i, REMOVE_QUOTES);
	i = 0;
	while (split[i])
	{
		free(*token_i);
		*token_i = ft_strjoin(aux, split[i]);
		free(aux);
		aux = ft_strdup(*token_i);
		i++;
	}
	free(aux);
	free_ptrptr(split);
}

static void	mark_quotes(char **token_i, int *j)
{
	char	c;
	
	c = (*token_i)[*j];
	(*token_i)[*j] = REMOVE_QUOTES;
	while ((*token_i)[*j] != c)
		(*j)++;
	(*token_i)[*j] = REMOVE_QUOTES;
}

void	remove_quotes(t_token *token_list)
{
	int		i;
	int		j;
	t_token	*aux;

	aux = token_list;
	while (aux)
	{
		i = 0;
		while (aux->token[i])
		{
			j = 0;
			while (aux->token[i][j])
			{
				if (aux->token[i][j] == '\'' || aux->token[i][j] == '\"')
					mark_quotes(&aux->token[i], &j);
				j++;
			}
			remove_quotes_aux(&aux->token[i]);
			i++;
		}
		aux = aux->next;
	}
}
